/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:51:47 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/08 18:49:32 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	destroy_structs_mutex(t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->info[N_PHILOS])
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			exit_philo(&data, E_DELMTX);
		if (pthread_mutex_destroy(&data->philos[i].lock))
			exit_philo(&data, E_DELMTX);
	}
	if (pthread_mutex_destroy(&data->lock))
		exit_philo(&data, E_DELMTX);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = init_data();
	parse_input(argc, argv, data);
	init_philos(data);
	start_threads(data);
	exit_philo(&data, 0);
	return (0);
}
