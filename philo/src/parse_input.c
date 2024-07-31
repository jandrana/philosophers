/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:09:11 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/31 17:35:34 by ana-cast         ###   ########.fr       */
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
		data->error = NO_ERROR;
	}
	return (data);
}

void	type_error(ssize_t value, int min, t_input *data)
{
	if (value < min)
	{
		if (value == 0)
			data->error = E_NOTPOS;
		else
			data->error = value;
	}
}

ssize_t	*find_arg(t_input *data, int pos)
{
	if (pos == N_PHILOS)
		return (&data->n_philos);
	else if (pos == T_DIE)
		return (&data->t_die);
	else if (pos == T_EAT)
		return (&data->t_eat);
	else if (pos == T_SLEEP)
		return (&data->t_sleep);
	else if (pos == NT_EAT)
		return (&data->nt_eat);
	else
		return (NULL);
}

int	check_data(t_input *data)
{
	int	error;

	if (data->n_philos <= 0)
		error = 1;
	else if (data->t_die < 0)
		error = 2;
	else if (data->t_eat < 0)
		error = 3;
	else if (data->t_sleep < 0)
		error = 4;
	else if (data->nt_eat == -1)
		error = 5;
	else
		return (0);
	if (error > 1)
		data->error = E_NEG;
	else
		data->error = E_NOTPOS;
	return (error);
}

t_input	*parse_input(int argc, char **input)
{
	t_input	*data;
	int		data_err;

	if (!input)
		return (put_error(E_NOMEM, NULL, 0));
	if (in_range(array_len(input), 4, 5))
		return (put_error(E_NARGS, NULL, 0));
	data = init_data();
	if (data)
	{
		data->n_philos = ph_un_atol(input[0]);
		data->t_die = ph_un_atol(input[1]);
		data->t_eat = ph_un_atol(input[2]);
		data->t_sleep = ph_un_atol(input[3]);
		if (array_len(input) == 5)
			data->nt_eat = ph_un_atol(input[4]);
		data_err = check_data(data);
		if (data_err)
			put_error(data->error, input[data_err - 1], data_err);
	}
	else
		put_error(E_NOMEM, NULL, 0);
	if (argc == 2)
		free_array(&input);
	return (data);
}
