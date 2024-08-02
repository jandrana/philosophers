/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:41 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/02 20:42:33 by ana-cast         ###   ########.fr       */
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

void	color_error(t_input *data, int pos, char *title, bool value)
{
	int		error;

	error = check_data(data, pos);
	if (array_len(data->input) <= pos && pos != 4)
		fprintf(stderr, YELLOW);
	if (value && error && array_len(data->input) > pos)
	{
		fprintf(stderr, "\n - %s = \"%s\" ", title, data->input[pos]);
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

void	print_output(t_input *data, bool value)
{
	if (!data)
		fprintf(stderr, OE_NOMEM WHITE);
	color_error(data, 0, ON_PHILOS, value);
	color_error(data, 1, OT_DIE, value);
	color_error(data, 2, OT_EAT, value);
	color_error(data, 3, OT_SLEEP, value);
	color_error(data, 4, ONT_EAT, value);
}

int	put_error(t_input *data, t_type_error type)
{
	if (data && (!data->errors || !in_range(array_len(data->input), 4, 5)))
		return (0);
	fprintf(stderr, RED BOLD "\nERROR:" WHITE);
	if (type == E_NOMEM)
		return (print_output(NULL, false), 1);
	fprintf(stderr, " ./philo ");
	print_output(data, false);
	print_output(data, true);
	if (array_len(data->input) > 5)
		fprintf(stderr, "\n - " RED OE_MARGS);
	else if (array_len(data->input) < 4)
		fprintf(stderr, "\n - " RED OE_NARGS);
	fprintf(stderr, "\n\n");
	return (data->errors);
}
