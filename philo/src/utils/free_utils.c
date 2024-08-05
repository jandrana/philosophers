/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:39 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/05 20:36:01 by ana-cast         ###   ########.fr       */
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

void	destroy_philos(t_data *data)
{
	int	id;

	id = -1;
	while (++id < data->input[N_PHILOS])
		pthread_mutex_destroy(&data->forks[id]);
	id = -1;
	while (++id < data->input[N_PHILOS])
		pthread_mutex_destroy(&data->philos[id].lock);
}

void	free_data(t_data **data)
{
	if (*data)
	{
		printf("NUM PHILOSOPHERS:%i\n\n", (*data)->input[N_PHILOS]);
		if ((*data)->philos && (*data)->forks)
			destroy_philos(*data);
		if ((*data)->philos)
			free((*data)->philos);
		if ((*data)->forks)
			free((*data)->forks);
		if ((*data)->input)
			free((*data)->input);
		pthread_mutex_destroy(&(*data)->lock);
		pthread_mutex_destroy(&(*data)->print);
		free(*data);
	}
}
