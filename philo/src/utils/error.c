/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:41 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/02 20:27:34 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

char	*error_title(t_type_error type)
{
	char	*new_title;

	new_title = NULL;
	if (type == E_NARGS)
		new_title = OE_NARGS;
	else if (type == E_NOTPOS)
		new_title = OE_NOTPOS;
	else if (type == E_OORL)
		new_title = OE_OORL;
	else if (type == E_NAN)
		new_title = OE_NAN;
	else if (type == E_NOMEM)
		new_title = OE_NOMEM;
	return (new_title);
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
