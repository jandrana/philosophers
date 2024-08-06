/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:39 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/06 14:10:02 by ana-cast         ###   ########.fr       */
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

int	exit_philo(t_data **data, t_input **input, int argc)
{
	int	exit_code;

	exit_code = NO_ERROR;
	if (*input)
	{
		exit_code = (*input)->errors;
		if ((*input)->args && argc == 2)
			free_array(&(*input)->args);
		else if (!(*input)->args)
			exit_code = put_error(NULL, E_NOMEM);
		free(*input);
	}
	else
		exit_code = put_error(NULL, E_NOMEM);
	if (exit_code == NO_ERROR)
	{
		if (*data)
			free_data(data);
		else
			exit_code = put_error(NULL, E_NOMEM);
	}
	return (exit_code);

}
