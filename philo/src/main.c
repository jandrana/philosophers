/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:51:47 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/05 20:48:28 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_input	*input;
	t_data	*data;
	int		error;

	input = init_input();
	if (!input)
		return (put_error(NULL, E_NOMEM));
	error = parse_input(argc, argv, input);
	data = init_data(input);
	if (!data)
		return (put_error(NULL, E_NOMEM));
	if (data)
		free_data(&data);
	if (argc == 2)
		free_array(&input->args);
	free(input);
	return (error);
}
