/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:51:47 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/12 13:26:09 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
