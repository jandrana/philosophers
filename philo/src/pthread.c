/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:17:43 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/09 20:04:54 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*dead_alive(void	*v_philo)
{
	t_philo	*philo;
	time_t	t_to_starve;

	philo = (t_philo *)v_philo;
	pthread_mutex_lock(&philo->data->lock);
	while (!philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->lock);
		t_to_starve = philo->hunger - time_ts(philo->data->t_start);
		if (t_to_starve < 0 && philo->status != EAT)
		{
			print_status(philo, DEAD);
			philo->data->stop = 1;
		}
		else
			my_usleep(t_to_starve - 10);
		pthread_mutex_lock(&philo->data->lock);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (NULL);
}

void	*routine(void	*v_philo)
{
	t_philo		*philo;
	pthread_t	schrodinger;

	philo = (t_philo *)v_philo;
	if (pthread_create(&schrodinger, NULL, &dead_alive, philo))
		exit_philo(&philo->data, E_NEWTH);
	if (philo->data->info[N_PHILOS] == 1)
	{
		while (!philo->data->stop)
			my_usleep(1);
		return (NULL);
	}
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
	pthread_mutex_lock(&data->lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->lock);
	return (NULL);
}

void	start_threads(t_data *data)
{
	int			i;
	pthread_t	th_sup;
	t_philo		*philos;

	philos = data->philos;
	data->start = time_ms(0);
	i = -1;
	gettimeofday(&data->t_start, NULL);
	while (++i < data->info[N_PHILOS])
	{
		if (pthread_create(&philos[i].th, NULL, &routine, &philos[i]))
			exit_philo(&data, E_NEWTH);
	}
	if (pthread_create(&th_sup, NULL, &check_complete, data))
		exit_philo(&data, E_NEWTH);
	i = -1;
	while (++i < data->info[N_PHILOS])
	{
		if (pthread_join(philos[i].th, NULL))
			exit_philo(&data, E_DETTH);
	}
}
