/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:33:52 by ana-cast          #+#    #+#             */
/*   Updated: 2024/09/09 20:09:04 by ana-cast         ###   ########.fr       */
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
		data->ready = 0;
		data->philos = NULL;
		data->th = NULL;
		data->error = 0;
		gettimeofday(&data->t_start, NULL);
	}
	return (data);
}

void	init_threads(t_data *data, int num_ph)
{
	int			i;

	i = -1;
	data->th = safe_calloc(sizeof(t_threads), &data);
	data->th->p_th = safe_calloc(sizeof(pthread_t) * num_ph, &data);
	data->th->p_lck = safe_calloc(sizeof(pthread_mutex_t) * num_ph, &data);
	data->th->fork = safe_calloc(sizeof(pthread_mutex_t) * num_ph, &data);
	if (pthread_mutex_init(&data->th->lock, NULL))
		exit_philo(&data, E_INITMTX);
	if (pthread_mutex_init(&data->th->lock, NULL))
		exit_philo(&data, E_INITMTX);
	if (pthread_mutex_init(&data->th->deadlock, NULL))
		exit_philo(&data, E_INITMTX);
	while (++i < data->info[N_PHILOS])
	{
		if (pthread_mutex_init(&data->th->p_lck[i], NULL))
			exit_philo(&data, E_INITMTX);
		if (pthread_mutex_init(&data->th->fork[i], NULL))
			exit_philo(&data, E_INITMTX);
	}
}

void	init_philos(t_data	*data)
{
	int			num_ph;
	int			i;

	num_ph = data->info[N_PHILOS];
	data->philos = safe_calloc(sizeof(t_philo) * num_ph, &data);
	init_threads(data, num_ph);
	i = -1;
	while (++i < num_ph)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].hunger = data->info[T_DIE];
		data->philos[i].status = THINK;
		data->philos[i].data = data;
		data->philos[i].th = data->th;
	}
}
