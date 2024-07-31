/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:41 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/31 16:49:23 by ana-cast         ###   ########.fr       */
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
	{
		fprintf(stderr, "invalid number of arguments: %i", pos);
		fprintf(stderr, BOLD "\n\nExpected Sintax:" WHITE " ./philo " RED);
		fprintf(stderr, "[MANDATORY_ARGS] " BLUE "_[OPTIONAL_ARGS]_\n\t\t\t");
		pos = 0;
		while ((pos == 4 && fprintf(stderr, "\n\t\t\t")) || pos < 5)
			put_type_arg(pos++);
		fprintf(stderr, WHITE "\n\n");
	}
	if (error == E_NOTPOS)
		fprintf(stderr, "expected a positive number for ssize_t:");
	else if (error == E_NEG)
		fprintf(stderr, "expected a non-negative number for ssize_t:");
	else if (error == E_OORL)
		fprintf(stderr, "received number out of range for ssize_t:");
	else if (error == E_NAN)
		fprintf(stderr, "did not receive number for expected ssize_t:");
	put_type_arg(pos);
	if (error != E_NARGS && error != E_NOMEM)
		fprintf(stderr, "=[%s]\n", str);
	else if (error == E_NOMEM)
		fprintf(stderr, "Out of memory\n");
	return (NULL);
}
