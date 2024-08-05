/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:33:52 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/05 20:51:32 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_input	*init_input(void)
{
	t_input	*input;

	input = (t_input *)malloc(sizeof(t_input));
	if (input)
	{
		input->n_philos = 0;
		input->t_die = 0;
		input->t_eat = 0;
		input->t_sleep = 0;
		input->nt_eat = 0;
		input->t_start = 0;
		input->args = NULL;
		input->errors = 0;
	}
	return (input);
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

t_data	*start_data(t_input *input)
{
	t_data	*data;
	int		i;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->input = (int *)calloc(5, sizeof(int));
	if (!data->input)
		return (free(data), NULL);
	i = -1;
	while (++i < 5)
		data->input[i] = *find_arg(input, i);
	data->philos = calloc(data->input[N_PHILOS], sizeof(t_philos));
	if (!data->philos)
		return (free(data->input), free(data), NULL);
	data->forks = calloc(data->input[N_PHILOS], sizeof(pthread_mutex_t));
	if (!data->forks)
		return (free(data->forks), free(data->input), free(data), NULL);
	return (data);
}

t_data	*init_data(t_input *input)
{
	t_data	*data;

	data = start_data(input);
	if (!data)
		return (NULL);
	init_philos(data);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->print, NULL);
	return (data);
}
