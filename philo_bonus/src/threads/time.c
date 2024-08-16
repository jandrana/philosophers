/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 13:38:39 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/16 14:36:16 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

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

int	my_usleep(t_time sleep, t_time current, struct timeval t_start)
{
	while (time_ts(t_start) - current < sleep)
		usleep(1);
	return (0);
}
