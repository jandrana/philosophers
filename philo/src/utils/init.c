/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:33:52 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/02 19:14:22 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_input	*init_data(void)
{
	t_input	*data;

	data = (t_input *)malloc(sizeof(t_input));
	if (data)
	{
		data->n_philos = LONG_MIN;
		data->t_die = LONG_MIN;
		data->t_eat = LONG_MIN;
		data->t_sleep = LONG_MIN;
		data->nt_eat = LONG_MIN;
		data->t_start = LONG_MIN;
		data->input = NULL;
		data->errors = 0;
	}
	return (data);
}
