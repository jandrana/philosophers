/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:34:13 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/14 12:53:38 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static char	*get_action_msg(int action)
{
	if (action == THINK)
		return (O_THINK);
	if (action == FORK)
		return (O_FORK);
	if (action == EAT)
		return (O_EAT);
	if (action == SLEEP)
		return (O_SLEEP);
	if (action == DEAD)
		return (O_DEAD);
	return (NULL);
}

t_time	print_status(t_philo *wise_man, int action)
{
	t_time	time;

	pthread_mutex_lock(&wise_man->th->lock);
	time = time_ts(wise_man->data->t_start);
	if (wise_man->data->stop)
	{
		pthread_mutex_unlock(&wise_man->th->lock);
		return (time);
	}
	if (wise_man->hunger < time && action != EAT)
		action = DEAD;
	if (action == DEAD)
	{
		printf("%lu %i %s", time, wise_man->id, O_DEAD);
		wise_man->data->stop = 1;
	}
	else
		printf("%lu %i %s", time, wise_man->id, get_action_msg(action));
	pthread_mutex_unlock(&wise_man->th->lock);
	return (time);
}

void	perform_routine(t_philo *philo)
{
	t_data	*data;
	t_time	current;

	data = philo->data;
	pthread_mutex_lock(&philo->th->fork[philo->id - 1]);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->th->fork[philo->id % data->info[N_PHILOS]]);
	philo->status = EAT;
	print_status(philo, FORK);
	current = print_status(philo, EAT);
	pthread_mutex_lock(&philo->th->p_lck[philo->id - 1]);
	philo->hunger = current + data->info[T_DIE];
	pthread_mutex_unlock(&philo->th->p_lck[philo->id - 1]);
	philo->meals++;
	my_usleep(data->info[T_EAT], current, data->t_start);
	current = print_status(philo, SLEEP);
	philo->status = SLEEP;
	pthread_mutex_unlock(&philo->th->fork[philo->id % data->info[N_PHILOS]]);
	pthread_mutex_unlock(&philo->th->fork[philo->id - 1]);
	my_usleep(data->info[T_SLEEP], current, data->t_start);
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

int	my_usleep(t_time sleep, t_time current, struct timeval t_start)
{
	while (time_ts(t_start) - current < sleep)
		usleep(1);
	return (0);
}
