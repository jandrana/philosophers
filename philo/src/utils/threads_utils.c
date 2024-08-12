/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:34:13 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/12 21:09:10 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

char	*get_action_msg(int action)
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

void	print_status(t_philo *wise_man, int action)
{
	uint64_t	time;

	pthread_mutex_lock(&wise_man->th->lock);
	time = time_ms(wise_man->data->start);
	if (!wise_man->data->stop)
		printf("%lu %i %s", time, wise_man->id, get_action_msg(action));
	pthread_mutex_unlock(&wise_man->th->lock);
}

static void	fight_for_forks(t_philo *philo)
{
	int		id;

	id = philo->id;
	pthread_mutex_lock(&philo->th->fork[id - 1]);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->th->fork[id % philo->data->info[N_PHILOS]]);
	print_status(philo, FORK);
}

void	perform_action(t_philo *philo, int action)
{
	t_data	*data;
	int		id;

	id = philo->id;
	data = philo->data;
	if (action == EAT)
	{
		fight_for_forks(philo);
		print_status(philo, EAT);
		philo->hunger = time_ts(data->t_start) + data->info[T_DIE];
		philo->status = EAT;
		philo->meals++;
		my_usleep(philo->data->info[T_EAT]);
	}
	else if (action == SLEEP)
	{
		print_status(philo, SLEEP);
		philo->status = SLEEP;
		pthread_mutex_unlock(&philo->th->fork[id - 1]);
		pthread_mutex_unlock(&philo->th->fork[id % data->info[N_PHILOS]]);
		my_usleep(data->info[T_SLEEP]);
	}
	else if (action == THINK)
		print_status(philo, THINK);
}
