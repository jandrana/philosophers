/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:17:43 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/12 20:24:50 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*schrodinger_monitor(void	*v_philo)
{
	t_philo	*philo;
	time_t	t_to_starve;

	philo = (t_philo *)v_philo;
	pthread_mutex_lock(&philo->th->lock);
	while (!philo->data->stop)
	{
		pthread_mutex_unlock(&philo->th->lock);
		t_to_starve = philo->hunger - time_ts(philo->data->t_start);
		pthread_mutex_lock(&philo->th->deadlock);
		if (t_to_starve < 0 && philo->status != EAT)
		{
			print_status(philo, DEAD);
			philo->data->stop = 1;
			pthread_mutex_lock(&philo->th->deadlock);
		}
		else
		{
			pthread_mutex_unlock(&philo->th->deadlock);
			my_usleep(t_to_starve - 10);
		}
		pthread_mutex_lock(&philo->th->lock);
	}
	pthread_mutex_unlock(&philo->th->lock);
	return (NULL);
}

void	*sync_start(t_philo *philo)
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
	if (pthread_create(&schrodinger, NULL, &dead_alive, philo))
		exit_philo(&philo->data, E_NEWTH);
	if (philo->id % 2 == 0)
		my_usleep(philo->data->info[T_EAT] / 2);
	while (!philo->data->stop)
	{
		fight_for_forks(philo);
		spaguetti_time(philo);
		share_forks_and_rest(philo);
	}
	return (NULL);
}

void	*check_complete(void *v_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)v_data;
	if (!data->info[NT_EAT])
		return (NULL);
	i = -1;
	while (data->info[N_PHILOS] && ++i < data->info[N_PHILOS] && !data->stop)
	{
		if (data->philos[i].meals < data->info[NT_EAT])
			i = -1;
	}
	pthread_mutex_lock(&data->th->lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->th->lock);
	return (NULL);
}
