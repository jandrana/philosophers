/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:10:39 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/07 19:28:39 by ana-cast         ###   ########.fr       */
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
