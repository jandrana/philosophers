/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:17:43 by ana-cast          #+#    #+#             */
/*   Updated: 2024/09/09 20:05:20 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	kill_children(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->info[N_PHILOS])
		kill(data->pid[i], SIGTERM);
}

void	wait_children(t_data *data)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status) || WIFSIGNALED(status))
		kill_children(data);
	data->error = WAIT_EXIT;
	sem_post(data->ready);
}

void	everyone_ready(t_data *data, bool start)
{
	int	i;

	i = -1;
	while (++i < data->info[N_PHILOS] && data->error != WAIT_EXIT)
	{
		sem_wait(data->ready);
		if (i + 1 != data->info[N_PHILOS] && !start && data->error != WAIT_EXIT)
			sem_post(data->print);
	}
	if (start)
	{
		gettimeofday(&data->t_start, NULL);
		my_usleep(100, time_ts(data->t_start), data->t_start);
		sem_post(data->start);
	}
	else if (data->error != WAIT_EXIT)
		kill_children(data);
}

void	start_threads(t_data *data)
{
	int			i;
	pthread_t	th_sup;

	i = -1;
	while (++i < data->info[N_PHILOS])
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			exit_philo(&data, E_TIME);
		if (data->pid[i] == 0)
			routine(&data->philos[i]);
		usleep(100);
	}
	everyone_ready(data, 1);
	if (pthread_create(&th_sup, NULL, &satisfaction_monitor, data))
		exit_philo(&data, E_NEWTH);
	wait_children(data);
	if (pthread_join(th_sup, NULL))
		exit_philo(&data, E_DETTH);
}

void	*satisfaction_monitor(void *v_data)
{
	t_data	*data;

	data = (t_data *)v_data;
	if (!data->info[NT_EAT])
		return (NULL);
	everyone_ready(data, 0);
	data->error = EXIT;
	return (NULL);
}
