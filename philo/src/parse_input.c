/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:09:11 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/05 19:41:45 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	*find_arg(t_input *input, int pos)
{
	if (pos == N_PHILOS)
		return (&input->n_philos);
	else if (pos == T_DIE)
		return (&input->t_die);
	else if (pos == T_EAT)
		return (&input->t_eat);
	else if (pos == T_SLEEP)
		return (&input->t_sleep);
	else if (pos == NT_EAT)
		return (&input->nt_eat);
	else
		return (NULL);
}

int	check_input(t_input	*input, int pos)
{
	long	error;

	if (pos < array_len(input->args))
	{
		error = ft_atoui(input->args[pos]);
		if (error < 1)
		{
			if (error == E_OORL)
				return (E_OORL);
			else if (error == E_NAN)
				return (E_NAN);
			else
				return (E_NOTPOS);
		}
	}
	return (NO_ERROR);
}

void	assign_input(t_input *input)
{
	int	len;
	int	i;

	i = -1;
	len = array_len(input->args);
	if (len > 5)
		len = 5;
	while (len > ++i && input->args[i])
	{
		*find_arg(input, i) = ft_atoui(input->args[i]);
		if (check_input(input, i))
			input->errors++;
	}
}

int	parse_input(int argc, char **argv, t_input *input)
{
	if (argc == 2)
		input->args = ph_split(argv[1], ' ');
	else
		input->args = argv + 1;
	if (!input->args)
		return (put_error(input, E_NOMEM));
	assign_input(input);
	return (put_error(input, 0));
}
