/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:11:50 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/08 16:17:36 by ana-cast         ###   ########.fr       */
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

uint64_t	time_ms(uint64_t start)
{
	struct timeval	time;
	int				errno;

	errno = gettimeofday(&time, NULL);
	if (errno)
		return (print_error(E_TIME, errno), 0);
	return ((time.tv_sec * 1000LL + time.tv_usec / 1000) - start);
}

int	my_usleep(uint64_t sleep)
{
	uint64_t	stop;

	stop = time_ms(0) + sleep;
	while (time_ms(0) < stop)
		;
	return (0);
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
