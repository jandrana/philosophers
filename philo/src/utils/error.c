/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:41 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/31 16:38:29 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	put_badarg(int bad_arg)
{
	if (bad_arg == 1)
		fprintf(stderr, "[number_of_philosophers]");
	if (bad_arg == 2)
		fprintf(stderr, "[time_to_die]");
	if (bad_arg == 3)
		fprintf(stderr, "[time_to_eat]");
	if (bad_arg == 4)
		fprintf(stderr, "[time_to_sleep]");
	if (bad_arg == 5)
		fprintf(stderr, "[times_each_philosopher_must_eat]");
}

void	*put_error(int error, char *str, int bad_arg)
{
	fprintf(stderr, "\t%s%s-philo: Error: %s", RED, BOLD, WHITE);
	if (error == E_NARGS)
		fprintf(stderr, "invalid number of arguments\n");
	if (error == E_NOTPOS || error == E_NEG)
	{
		put_badarg(bad_arg);
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
