/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:33:52 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/07 19:19:47 by ana-cast         ###   ########.fr       */
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
		data->threads = NULL;
		data->error = 0;
	}
	return (data);
}

void	init_philos(t_data	*data)
{
	int	id;

	id = -1;
	while (++id < data->input[N_PHILOS])
		pthread_mutex_init(&data->forks[id], NULL);
	id = -1;
	while (++id < data->input[N_PHILOS])
	{
		data->philos[id].id = id;
		data->philos[id].death = data->input[T_DIE];
		data->philos[id].action = THINK;
		data->philos[id].nb_eat = 0;
		data->philos[id].right_fk = &data->forks[id];
		if (id == 1)
			data->philos[id].left_fk = &data->forks[data->input[N_PHILOS]];
		else
			data->philos[id].left_fk = &data->forks[id - 1];
		pthread_mutex_init(&data->philos[id].lock, NULL);
	}
}

void	init_philos(t_data	*data)
{
	int			num_ph;
	int			i;

	num_ph = data->info[N_PHILOS];
	data->philos = safe_calloc(sizeof(t_philo) * num_ph, &data);
	malloc_threads(data, data->info[N_PHILOS]);
	i = -1;
	while (++i < num_ph)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].hunger = 0;
		data->philos[i].status = THINK;
		data->philos[i].data = data;
	}
	data->start = get_time_ms(0);
}
