/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:17:43 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/12 21:08:33 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*sync_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->th->lock);
	philo->data->ready += 1;
	pthread_mutex_unlock(&philo->th->lock);
	while (true)
	{
		pthread_mutex_lock(&philo->th->lock);
		if (philo->data->ready == philo->data->info[N_PHILOS] && philo->id == 1)
		{
			philo->data->start = time_ms(0);
			gettimeofday(&philo->data->t_start, NULL);
			pthread_mutex_unlock(&philo->th->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->th->lock);
		if (philo->data->start)
		{
			if (philo->id % 2 == 0)
				my_usleep(philo->data->info[T_EAT] / 2);
			return (NULL);
		}
	}
}

void	*lonely_philo(void	*v_philo)
{
	t_philo		*philo;

	philo = (t_philo *)v_philo;
	sync_start(philo);
	pthread_mutex_lock(&philo->th->fork[philo->id - 1]);
	print_status(philo, FORK);
	pthread_mutex_unlock(&philo->th->fork[philo->id - 1]);
	my_usleep(philo->data->info[T_DIE] - time_ms(philo->data->start));
	while (time_ms(philo->data->start) < (uint64_t)philo->data->info[T_DIE])
		my_usleep(1);
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
		perform_action(philo, THINK);
	}
	return (NULL);
}
