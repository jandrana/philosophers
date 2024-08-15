/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:33:52 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/15 21:08:05 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_START);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_READY);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_EAT);
}

void	open_semaphores(t_data *data)
{
	unlink_semaphores();
	data->forks = sem_open(SEM_FORK, O_CREAT | O_EXCL, S_IRWXU, \
		data->info[N_PHILOS]);
	if (data->forks == SEM_FAILED)
		exit_philo(&data, errno);
	data->start = sem_open(SEM_START, O_CREAT | O_EXCL, S_IRWXU, 0);
	if (data->start == SEM_FAILED)
		exit_philo(&data, errno);
	data->stop = sem_open(SEM_STOP, O_CREAT | O_EXCL, S_IRWXU, 0);
	if (data->stop == SEM_FAILED)
		exit_philo(&data, errno);
	data->ready = sem_open(SEM_READY, O_CREAT | O_EXCL, S_IRWXU, 0);
	if (data->ready == SEM_FAILED)
		exit_philo(&data, errno);
	data->print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, S_IRWXU, 1);
	if (data->print == SEM_FAILED)
		exit_philo(&data, errno);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data)
	{
		data->args = NULL;
		data->info = safe_calloc(sizeof(int) * 5, &data);
		data->forks = (sem_t *) 0;
		data->start = 0;
		data->stop = (sem_t *) 0;
		data->ready = (sem_t *) 0;
		data->print = (sem_t *) 0;
		data->philos = NULL;
		data->error = 0;
	}
	return (data);
}

void	init_philos(t_data	*data)
{
	int			num_ph;
	int			i;

	num_ph = data->info[N_PHILOS];
	data->philos = safe_calloc(sizeof(t_philo) * num_ph, &data);
	data->pid = safe_calloc(sizeof(pid_t) * num_ph, &data);
	open_semaphores(data);
	i = -1;
	while (++i < num_ph)
	{
		data->philos[i].id = i + 1;
		data->philos[i].hunger = data->info[T_DIE];
		data->philos[i].status = THINK;
		data->philos[i].meals = 0;
		data->philos[i].eat = sem_open(SEM_EAT, O_CREAT, S_IRWXU, 1);
		if (data->philos[i].eat == SEM_FAILED)
			exit_philo(&data, errno);
		data->philos[i].data = data;
	}
}
