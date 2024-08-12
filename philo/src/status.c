/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:53:58 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/12 20:38:16 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	fight_for_forks(t_philo *philo)
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
