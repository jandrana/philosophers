/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:41 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/06 13:55:51 by ana-cast         ###   ########.fr       */
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

void	color_error(t_input *input, int pos, char *title, bool value)
{
	int		error;

	error = check_input(input, pos);
	if (array_len(input->args) <= pos && pos != 4)
		fprintf(stderr, YELLOW);
	if (value && error && array_len(input->args) > pos)
	{
		fprintf(stderr, "\n - %s = \"%s\" ", title, input->args[pos]);
		fprintf(stderr, "%s", error_title(error));
	}
	else if (!value)
	{
		if (error)
			fprintf(stderr, RED);
		fprintf(stderr, "%s", title);
	}
	fprintf(stderr, WHITE);
}

void	print_output(t_input *input, bool value)
{
	if (!input)
		fprintf(stderr, RED BOLD "\nERROR:" WHITE OE_NOMEM WHITE "\n");
	else
	{
		color_error(input, 0, ON_PHILOS, value);
		color_error(input, 1, OT_DIE, value);
		color_error(input, 2, OT_EAT, value);
		color_error(input, 3, OT_SLEEP, value);
		color_error(input, 4, ONT_EAT, value);
	}
}

int	put_error(t_input *input, t_type_error type)
{
	if (type == E_NOMEM || !input)
		return (print_output(NULL, false), E_NOMEM);
	if (array_len(input->args) < 4 || array_len(input->args) > 5)
		input->errors++;
	if (!input->errors)
		return (NO_ERROR);
	fprintf(stderr, RED BOLD "\nERROR:" WHITE);
	fprintf(stderr, " ./philo ");
	print_output(input, false);
	print_output(input, true);
	if (array_len(input->args) > 5)
		fprintf(stderr, "\n - " RED OE_MARGS);
	else if (array_len(input->args) < 4)
		fprintf(stderr, "\n - " RED OE_NARGS);
	fprintf(stderr, "\n\n");
	return (input->errors);
}
