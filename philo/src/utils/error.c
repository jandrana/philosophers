/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:41 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/09 19:45:54 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

char	*error_title(int type)
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
	else if (type == E_INITMTX)
		new_title = OE_INITMTX;
	else if (type == E_DELMTX)
		new_title = OE_DELMTX;
	else if (type == E_NEWTH)
		new_title = OE_NEWTH;
	else if (type == E_NOMEM)
		new_title = OE_NOMEM;
	else if (type == E_DETTH)
		new_title = OE_DETTH;
	else if (type == E_TIME)
		new_title = OE_TIME;
	return (new_title);
}

void	color_error(t_data *data, int pos, char *title, bool value)
{
	int		error;

	error = check_args(data, pos);
	if (array_len(data->args) <= pos && pos != 4)
		fprintf(stderr, YELLOW);
	if (value && error && array_len(data->args) > pos)
	{
		fprintf(stderr, "\n - %s = \"%s\" ", title, data->args[pos]);
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

void	print_output(t_data *data, bool value)
{
	if (!data)
		fprintf(stderr, RED BOLD "\nERROR:" WHITE OE_NOMEM WHITE "\n");
	else
	{
		color_error(data, 0, ON_PHILOS, value);
		color_error(data, 1, OT_DIE, value);
		color_error(data, 2, OT_EAT, value);
		color_error(data, 3, OT_SLEEP, value);
		color_error(data, 4, ONT_EAT, value);
	}
}

int	check_parsing(t_data *data)
{
	if (!data)
		return (print_error(E_NOMEM, ENOMEM));
	if (array_len(data->args) < 4 || array_len(data->args) > 5)
		data->error++;
	if (!data->error)
		return (NO_ERROR);
	fprintf(stderr, RED BOLD "\nERROR:" WHITE);
	fprintf(stderr, " ./philo ");
	print_output(data, false);
	print_output(data, true);
	if (array_len(data->args) > 5)
		fprintf(stderr, "\n - " RED OE_MARGS);
	else if (array_len(data->args) < 4)
		fprintf(stderr, "\n - " RED OE_NARGS);
	fprintf(stderr, "\n\n");
	return (data->error);
}

int	print_error(t_error type, int n_err)
{
	char	*error_msg;

	if (type == NO_ERROR)
		return (NO_ERROR);
	fprintf(stderr, RED BOLD "\nERROR:" WHITE);
	if (type == E_TIME)
		fprintf(stderr, OE_TIME ": %s\n", strerror(n_err));
	else
		error_msg = error_title(type);
	if (type)
		fprintf(stderr, "%s" WHITE, error_msg);
	fprintf(stderr, "\n\n");
	return (n_err);
}
