/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:34:13 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/13 20:52:16 by ana-cast         ###   ########.fr       */
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

static void	fight_for_forks(t_philo *philo)
{
	int		id;
	int		right;
	int		left;

	id = philo->id;
	right = id - 1;
	left = id % philo->data->info[N_PHILOS];
	pthread_mutex_lock(&philo->th->fork[right]);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->th->fork[left]);
	philo->status = EAT;
	print_status(philo, FORK);
}

void	perform_action(t_philo *philo, int action)
{
	t_data	*data;
	int		id;
	t_time	current;

	id = philo->id;
	data = philo->data;
	if (action == EAT)
	{
		fight_for_forks(philo);
		current = print_status(philo, EAT);
		pthread_mutex_lock(&philo->th->p_lck[philo->id - 1]);
		philo->hunger = current + data->info[T_DIE];
		pthread_mutex_unlock(&philo->th->p_lck[philo->id - 1]);
		philo->meals++;
		my_usleep(data->info[T_EAT], current, data->t_start);
	}
	else if (action == SLEEP)
	{
		current = print_status(philo, SLEEP);
		philo->status = SLEEP;
		pthread_mutex_unlock(&philo->th->fork[id % data->info[N_PHILOS]]);
		pthread_mutex_unlock(&philo->th->fork[id - 1]);
		my_usleep(data->info[T_SLEEP], current, data->t_start);
	}
}
