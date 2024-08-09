/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:11:50 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/09 19:55:42 by ana-cast         ###   ########.fr       */
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
	return (time.tv_sec * 1000LL + (time.tv_usec) / 1000 - (long)start);
}

uint64_t	time_ts(struct timeval t_start)
{
	struct timeval	time;
	int				errno;
	long			sec;

	errno = gettimeofday(&time, NULL);
	if (errno)
		return (print_error(E_TIME, errno), 0);
	sec = time.tv_sec * 1000LL - (t_start.tv_sec * 1000LL);
	return (sec + (time.tv_usec - t_start.tv_usec) / 1000);
}

int	my_usleep(uint64_t sleep)
{
	uint64_t	stop;

	stop = time_ms(0) - 1 + sleep;
	while (time_ms(0) <= stop)
		usleep(1);
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
