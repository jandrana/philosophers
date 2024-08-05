/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:09:11 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/05 17:40:51 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

uint64_t	*find_arg(t_input *data, int pos)
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
	uint64_t	arg_to_check;
	long long	error;

	arg_to_check = *find_arg(data, pos);
	if (arg_to_check > UINT32_MAX)
	{
		error = ft_atoll(data->input[pos]);
		if (error == E_OORL)
			return (E_OORL);
		else if (error == E_NAN)
			return (E_NAN);
		else
			return (E_NOTPOS);
	}
	return (NO_ERROR);
}

void	assign_data(t_input *data)
{
	int			len;
	int			i;
	uint64_t	result;

	i = -1;
	len = array_len(data->input);
	if (len > 5)
		len = 5;
	while (len > ++i && data->input[i])
	{
		result = ft_atoll(data->input[i]);
		*find_arg(data, i) = result;
		if (check_data(data, i))
			data->errors++;
	}
}

int	parse_input(int argc, char **argv, t_input *data)
{
	if (argc == 2)
		data->input = ph_split(argv[1], ' ');
	else
		data->input = argv + 1;
	if (!data->input)
		return (put_error(data, E_NOMEM));
	assign_data(data);
	return (put_error(data, 0));
}
