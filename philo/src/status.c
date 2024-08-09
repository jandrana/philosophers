/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:53:58 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/09 20:06:32 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	fight_for_forks(t_philo *philo)
{
	int	right;
	int	left;

	right = philo->id - 1;
	left = philo->id % philo->data->info[N_PHILOS];
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->data->forks[right]);
		pthread_mutex_lock(&philo->data->forks[left]);
		print_status(philo, FORK);
		print_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		pthread_mutex_lock(&philo->data->forks[right]);
		print_status(philo, FORK);
		print_status(philo, FORK);
	}
}


void	spaguetti_time(t_philo *philo)
{
	print_status(philo, EAT);
	philo->hunger = time_ts(philo->data->t_start) + philo->data->info[T_DIE];
	philo->status = EAT;
	philo->meals++;
	my_usleep(philo->data->info[T_EAT]);
	print_status(philo, SLEEP);
	philo->status = SLEEP;
}

void	share_forks_and_rest(t_philo *philo)
{
	int	right;
	int	left;

	right = philo->id - 1;
	left = philo->id % philo->data->info[N_PHILOS];
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->data->forks[left]);
		pthread_mutex_unlock(&philo->data->forks[right]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[right]);
		pthread_mutex_unlock(&philo->data->forks[left]);
	}
	my_usleep(philo->data->info[T_SLEEP]);
	print_status(philo, THINK);
}

void	increase_wisdom(t_philo *philo)
{
	print_status(philo, THINK);
}
