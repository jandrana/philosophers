/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:51:47 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/30 20:48:51 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_input	*input;

	input = NULL;
	if (argc < 2)
		put_error(E_NARGS, NULL, 0);
	else if (argc == 2)
		input = parse_input(argc, ph_split(argv[1], ' '));
	else
		input = parse_input(argc, ++argv);
	if (input)
		print_input(input);
	return (0);
}
