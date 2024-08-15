/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:09:11 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/14 17:04:51 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	check_args(t_data *data, int pos)
{
	long	error;

	if (pos < array_len(data->args))
	{
		error = ft_atoui(data->args[pos]);
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

void	assign_info(t_data *data)
{
	int	len;
	int	i;

	len = array_len(data->args);
	if (len > 5)
		len = 5;
	i = -1;
	while (len > ++i && data->args[i])
	{
		data->info[i] = ft_atoui(data->args[i]);
		if (check_args(data, i))
			data->error++;
	}
}

char	**strarray_dup(char **src)
{
	char	**dup;
	int		i;

	dup = safe_calloc(sizeof(char *) * (array_len(src) + 1), NULL);
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < array_len(src))
		dup[i] = ft_strdup(src[i]);
	dup[i] = NULL;
	return (dup);
}

void	parse_input(int argc, char **argv, t_data *data)
{
	if (!data)
		exit_philo(NULL, E_NOMEM);
	if (argc == 2)
		data->args = split(argv[1], ' ');
	else
		data->args = strarray_dup(argv + 1);
	if (!data->args)
		exit_philo(&data, E_NOMEM);
	assign_info(data);
	if (check_parsing(data))
		exit_philo(&data, 0);
}
