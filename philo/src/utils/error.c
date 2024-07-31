/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:41 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/31 16:46:10 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

char	*put_type_error(int error)
{
	if (error == E_NARGS)
		return ("`E_NARGS'");
	else if (error == E_NOTPOS)
		return ("`E_NOTPOS'");
	else if (error == E_NEG)
		return ("`E_NEG'");
	else if (error == E_OORL)
		return ("`E_OORL'");
	else if (error == E_NAN)
		return ("`E_NAN'");
	else if (error == E_NOMEM)
		return ("`E_NOMEM'");
	else
		return ("`SYNTAX_ERROR'");
}

void	put_type_arg(int pos)
{
	if (pos == N_PHILOS)
		fprintf(stderr, RED " [number_of_philosophers]" WHITE);
	if (pos == T_DIE)
		fprintf(stderr, RED " [time_to_die]" WHITE);
	if (pos == T_EAT)
		fprintf(stderr, RED " [time_to_eat]" WHITE);
	if (pos == T_SLEEP)
		fprintf(stderr, RED " [time_to_sleep]" WHITE);
	if (pos == NT_EAT)
		fprintf(stderr, BLUE " _[times_each_philosopher_must_eat]_" WHITE);
}

void	*put_error(int error, char *str, int pos)
{
	fprintf(stderr, RED BOLD "Error: %s " WHITE, put_type_error(error));
	if (error == E_NARGS)
		fprintf(stderr, "invalid number of arguments\n");
	if (error == E_NOTPOS || error == E_NEG)
	{
		put_type_arg(pos);
		fprintf(stderr, "=[%s] ", str);
		if (error == E_NEG)
			fprintf(stderr, "must be a number greater than 0\n");
		else
			fprintf(stderr, "must be a positive number\n");
	}
	else if (error == E_NOMEM)
		fprintf(stderr, "Out of memory\n");
	return (NULL);
}
