/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:51:47 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/02 20:22:22 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_input	*data;
	int		error;

	data = init_data();
	if (!data)
		return (put_error(NULL, E_NOMEM));
	error = parse_input(argc, argv, data);
	if (data && error == NO_ERROR)
		print_input(data);
	if (argc == 2)
		free_array(&data->input);
	free(data);
	return (error);
}
