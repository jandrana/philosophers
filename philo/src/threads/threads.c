/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:17:43 by ana-cast          #+#    #+#             */
/*   Updated: 2024/09/09 20:33:30 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*get_routine_to_execute(t_data *data)
{
	void	*exec_routine;

	if (data->info[N_PHILOS] == 1)
		exec_routine = &lonely_philo;
	else
		exec_routine = &routine;
	return (exec_routine);
}

static void	wait_ready(t_data *data)
{
	pthread_mutex_lock(&data->th->lock);
	while (data->ready != data->info[N_PHILOS])
	{
		pthread_mutex_unlock(&data->th->lock);
		my_usleep(10, time_ts(data->t_start), data->t_start);
		pthread_mutex_lock(&data->th->lock);
	}
}

void	start_threads(t_data *data)
{
	int			i;
	pthread_t	th_sup;
	void		*exec;

	exec = get_routine_to_execute(data);
	i = -1;
	while (++i < data->info[N_PHILOS])
	{
		if (pthread_create(&data->th->p_th[i], NULL, exec, &data->philos[i]))
			exit_philo(&data, E_NEWTH);
	}
	if (pthread_create(&th_sup, NULL, &greed_supervisor, data))
		exit_philo(&data, E_NEWTH);
	i = -1;
	wait_ready(data);
	data->start = 1;
	gettimeofday(&data->t_start, NULL);
	while (++i < data->info[N_PHILOS])
	{
		if (pthread_join(data->th->p_th[i], NULL))
			exit_philo(&data, E_DETTH);
	}
}

void	*schrodinger_monitor(void *v_philo)
{
	t_philo	*philo;
	t_time	t_to_starve;

	philo = (t_philo *)v_philo;
	while (!philo->data->stop)
	{
		pthread_mutex_lock(&philo->th->p_lck[philo->id - 1]);
		t_to_starve = philo->hunger - time_ts(philo->data->t_start);
		pthread_mutex_unlock(&philo->th->p_lck[philo->id - 1]);
		if (t_to_starve <= 0 && philo->status != EAT)
			print_status(philo, DEAD);
		else
			my_usleep(5, time_ts(philo->data->t_start), \
				philo->data->t_start);
	}
	return (NULL);
}

void	*greed_supervisor(void *v_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)v_data;
	if (!data->info[NT_EAT])
		return (NULL);
	i = -1;
	while (data->info[N_PHILOS] && ++i < data->info[N_PHILOS] && !data->stop)
	{
		if (data->philos[i].meals < data->info[NT_EAT])
			i = -1;
	}
	pthread_mutex_lock(&data->th->lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->th->lock);
	return (NULL);
}
