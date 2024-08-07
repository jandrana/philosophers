/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:34:13 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/07 19:27:02 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_input(t_data *data)
{
	printf("[N PHILOS/FORKS]= %i\n", data->info[N_PHILOS]);
	printf("[TIME_TO_DIE]= %i\n", data->info[T_DIE]);
	printf("[TIME_TO_EAT]= %i\n", data->info[T_EAT]);
	printf("[TIME_TO_SLEEP]= %i\n", data->info[T_SLEEP]);
	printf("[TIMES_EACH_PHILO_MUST_EAT]= %i\n", data->info[NT_EAT]);
}
