/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:39 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/12 13:26:12 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

char	*free_str(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

void	free_array(char ***array)
{
	int	i;

	i = -1;
	if (*array)
	{
		while ((*array)[++i])
			free((*array)[i]);
		free(*array);
		*array = NULL;
	}
}

void	destroy_structs_mutex(t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->info[N_PHILOS])
	{
		if (pthread_mutex_destroy(&data->th->fork[i]))
			exit_philo(&data, E_DELMTX);
		if (pthread_mutex_destroy(&data->th->p_lck[i]))
			exit_philo(&data, E_DELMTX);
	}
	if (pthread_mutex_destroy(&data->th->lock))
		exit_philo(&data, E_DELMTX);
}

void	free_data(t_data **data)
{
	if (*data)
	{
		if ((*data)->philos)
			free((*data)->philos);
		if ((*data)->info)
			free((*data)->info);
		if ((*data)->args)
			free_array(&(*data)->args);
		if ((*data)->th)
		{
			free((*data)->th->p_th);
			free((*data)->th->p_lck);
			free((*data)->th->fork);
			free((*data)->th);
		}
		free(*data);
	}
}

void	exit_philo(t_data **data, int error)
{
	int	exit_code;

	exit_code = error;
	if (*data)
	{
		if (exit_code != NO_ERROR)
			destroy_structs_mutex(*data);
		if (!(*data)->args)
			exit_code = E_NOMEM;
		free_data(data);
	}
	else if (!exit_code)
		exit_code = E_NOMEM;
	if (exit_code != NO_ERROR)
		print_error(error, 0);
	exit(exit_code);
}
