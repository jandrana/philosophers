/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:39 by ana-cast          #+#    #+#             */
/*   Updated: 2024/09/09 20:05:04 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

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

void	close_semaphores(t_data *data)
{
	if (data->forks)
		sem_close(data->forks);
	if (data->stop)
		sem_close(data->stop);
	if (data->ready)
		sem_close(data->ready);
	if (data->print)
		sem_close(data->print);
	if (data->start)
		sem_close(data->start);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_START);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_READY);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_EAT);
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
		if ((*data)->pid)
			free((*data)->pid);
		free(*data);
	}
}

void	exit_philo(t_data **data, int error)
{
	int	exit_code;

	exit_code = error;
	if (*data)
	{
		close_semaphores(*data);
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
