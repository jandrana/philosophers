/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:33:52 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/12 13:13:51 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data)
	{
		data->args = NULL;
		data->info = safe_calloc(sizeof(int) * 5, &data);
		data->stop = 0;
		data->start = 0;
		data->philos = NULL;
		data->th = NULL;
		data->error = 0;
	}
	return (data);
}

void	malloc_threads(t_data *data, int num_ph)
{
	t_threads	*th;

	data->threads = safe_calloc(sizeof(t_threads), &data);
	th = data->threads;
	th->philo = safe_calloc(sizeof(pthread_t) * num_ph, &data);
	th->ph_lock = safe_calloc(sizeof(pthread_mutex_t) * num_ph, &data);
	th->fork = safe_calloc(sizeof(pthread_mutex_t) * num_ph, &data);
}

void	init_structs_mutex(t_data *data)
{
	int			i;

	i = -1;
	if (pthread_mutex_init(&data->threads->print, NULL))
		exit_philo(&data, E_INITMTX);
	if (pthread_mutex_init(&data->threads->lock, NULL))
		exit_philo(&data, E_INITMTX);
	while (++i < data->info[N_PHILOS])
	{
		if (pthread_mutex_init(&data->threads->ph_lock[i], NULL))
			exit_philo(&data, E_INITMTX);
		if (pthread_mutex_init(&data->threads->fork[i], NULL))
			exit_philo(&data, E_INITMTX);
	}
}

void	init_data_mutex(t_data *data)
{
	int	num_ph;
	int	i;

	num_ph = data->info[N_PHILOS];
	data->forks = safe_calloc(sizeof(pthread_mutex_t) * num_ph, &data);
	i = -1;
	while (++i < data->info[N_PHILOS])
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			exit_philo(&data, E_INITMTX);
	}
}

void	init_philos(t_data	*data)
{
	int			num_ph;
	int			i;

	num_ph = data->info[N_PHILOS];
	data->philos = safe_calloc(sizeof(t_philo) * num_ph, &data);
	init_data_mutex(data);
	i = -1;
	while (++i < num_ph)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].hunger = data->info[T_DIE];
		data->philos[i].status = THINK;
		data->philos[i].data = data;
		data->philos[i].th = 0;
		data->philos[i].right = &data->forks[i];
		data->philos[i].left = &data->forks[(i + 1) % num_ph];
		if (pthread_mutex_init(&data->philos[i].lock, NULL))
			exit_philo(&data, E_INITMTX);
	}
}
