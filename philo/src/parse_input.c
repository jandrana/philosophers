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

void	assign_data(t_input *data)
{
	int		len;
	int		i;

	i = -1;
	len = array_len(data->input);
	if (len > 5)
		len = 5;
	while (len > ++i && data->input[i])
	{
		*find_arg(data, i) = ph_un_atol(data->input[i]);
		if (check_data(data, i))
			data->errors++;
	}
}

int	parse_input(int argc, char **argv, t_input *data)
{
	if (argc == 2)
		free_array(&input);
	return (data);
}
