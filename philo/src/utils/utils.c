/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:11:50 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/05 13:55:51 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	array_len(char **array)
{
	int	len;

	len = -1;
	while (array[++len])
		;
	return (len);
}

bool	in_range(ssize_t value, ssize_t min, ssize_t max)
{
	if (value >= min && value <= max)
		return (0);
	return (1);
}
