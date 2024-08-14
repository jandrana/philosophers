/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:17:43 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/13 20:35:53 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*sync_start(t_philo *philo)
{
	struct timeval	start;

	start = philo->data->t_start;
	pthread_mutex_lock(&philo->th->lock);
	philo->data->ready += 1;
	pthread_mutex_unlock(&philo->th->lock);
	while (true)
	{
		if (philo->data->start)
		{
			if (philo->id % 2 == 0)
				my_usleep(philo->data->info[T_EAT] / 2, time_ts(start), start);
			return (NULL);
		}
	}
}

void	*lonely_philo(void	*v_philo)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)v_philo;
	data = philo->data;
	sync_start(philo);
	pthread_mutex_lock(&philo->th->fork[philo->id - 1]);
	print_status(philo, FORK);
	pthread_mutex_unlock(&philo->th->fork[philo->id - 1]);
	while (time_ts(data->t_start) < (uint64_t)data->info[T_DIE])
		my_usleep(1, time_ts(data->t_start), data->t_start);
	print_status(philo, DEAD);
	return (NULL);
}

void	*routine(void	*v_philo)
{
	t_philo		*philo;
	pthread_t	schrodinger;

	philo = (t_philo *)v_philo;
	sync_start(philo);
	if (pthread_create(&schrodinger, NULL, &schrodinger_monitor, philo))
		exit_philo(&philo->data, E_NEWTH);
	while (!philo->data->stop)
	{
		perform_action(philo, EAT);
		perform_action(philo, SLEEP);
		print_status(philo, THINK);
	}
	return (NULL);
}
