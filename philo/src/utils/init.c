/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:33:52 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/05 16:49:01 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_input	*init_data(void)
{
	t_input	*data;

	data = (t_input *)malloc(sizeof(t_input));
	if (data)
	{
		data->n_philos = 0;
		data->t_die = 0;
		data->t_eat = 0;
		data->t_sleep = 0;
		data->nt_eat = 0;
		data->t_start = 0;
		data->input = NULL;
		data->errors = 0;
	}
	return (data);
}
