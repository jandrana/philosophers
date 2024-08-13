/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:11:50 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/13 16:53:08 by ana-cast         ###   ########.fr       */
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

t_time	timestamp_ms(void)
{
	struct timeval	time;
	int				errno;

	errno = gettimeofday(&time, NULL);
	if (errno)
		return (print_error(E_TIME, errno), 0);
	return (time.tv_sec * 1000LL + (time.tv_usec) / 1000);
}

int	my_usleep(uint64_t sleep)
{
	uint64_t	stop;

	stop = time_ms(0) - 1 + sleep;
	while (time_ms(0) <= stop)
		usleep(1);
	return (0);
}
