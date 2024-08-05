/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:34:13 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/05 18:28:27 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_input(t_input *input)
{
	printf("[N PHILOS/FORKS]= %i\n", input->n_philos);
	printf("[TIME_TO_DIE]= %i\n", input->t_die);
	printf("[TIME_TO_EAT]= %i\n", input->t_eat);
	printf("[TIME_TO_SLEEP]= %i\n", input->t_sleep);
	printf("[TIMES_EACH_PHILO_MUST_EAT]= %i\n", input->nt_eat);
}
