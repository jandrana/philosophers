/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:39 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/12 20:27:57 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*safe_calloc(size_t size, void *p_free)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (!ptr)
		exit_philo(p_free, E_NOMEM);
	memset(ptr, 0, size);
	return (ptr);
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
	if (pthread_mutex_destroy(&data->th->deadlock))
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
