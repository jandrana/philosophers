/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:34:13 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/16 18:41:19 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

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

	sem_wait(wise_man->data->print);
	time = time_ts(wise_man->data->t_start);
	if (wise_man->hunger < time && action != EAT)
		action = DEAD;
	if (action == EAT)
		printf("%lu %i %s", time, wise_man->id, O_FORK);
	if (action == DEAD)
	{
		printf("%lu %i %s", time, wise_man->id, O_DEAD);
		exit(EXIT_SUCCESS);
	}
	else
		printf("%lu %i %s", time, wise_man->id, get_action_msg(action));
	sem_post(wise_man->data->print);
	return (time);
}

void	perform_routine(t_philo *philo)
{
	t_data	*data;
	t_time	current;

	data = philo->data;
	sem_wait(data->forks);
	print_status(philo, FORK);
	sem_wait(data->forks);
	current = print_status(philo, EAT);
	philo->hunger = current + data->info[T_DIE];
	philo->status = EAT;
	philo->meals++;
	my_usleep(data->info[T_EAT], current, data->t_start);
	philo->status = SLEEP;
	if (philo->meals == data->info[NT_EAT])
	{
		sem_wait(data->print);
		sem_post(data->ready);
	}
	current = print_status(philo, SLEEP);
	sem_post(data->forks);
	sem_post(data->forks);
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
