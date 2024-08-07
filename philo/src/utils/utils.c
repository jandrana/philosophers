/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:11:50 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/07 21:51:46 by ana-cast         ###   ########.fr       */
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

void	*safe_calloc(size_t size, void *p_free)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (!ptr)
		exit_philo(p_free, E_NOMEM);
	memset(ptr, 0, size);
	return (ptr);
}
