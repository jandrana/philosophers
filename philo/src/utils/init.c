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
	return (data);
}
