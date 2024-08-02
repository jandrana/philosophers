/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:09:11 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/02 20:27:41 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

int	check_data(t_input	*data, int pos)
{
	ssize_t	arg_to_check;

	arg_to_check = *find_arg(data, pos);
	if (arg_to_check <= 0)
	{
		if (arg_to_check == 0)
			return (E_NOTPOS);
		else
			return (arg_to_check);
	}
	return (NO_ERROR);
}

t_input	*parse_input(int argc, char **input)
{
	t_input	*data;
	int		i;

	data = init_data();
	if (!input || !data)
		return (put_error(E_NOMEM, NULL, -1));
	if (in_range(array_len(input), 4, 5))
		return (put_error(E_NARGS, NULL, array_len(input)));
	i = -1;
	while (data->error == NO_ERROR && array_len(input) > ++i && input[i])
	{
		*find_arg(data, i) = ph_un_atol(input[i]);
		check_data(data, i);
	}
	if (data->error)
		put_error(data->error, input[i], i);
	if (argc == 2)
		free_array(&input);
	return (data);
}
