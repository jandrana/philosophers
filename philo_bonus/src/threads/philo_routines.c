/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:17:43 by ana-cast          #+#    #+#             */
/*   Updated: 2024/09/09 20:04:40 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	sync_start(t_philo *philo)
{
	struct timeval	*start;
	struct timeval	wait;

	sem_post(philo->data->ready);
	sem_wait(philo->data->start);
	sem_post(philo->data->start);
	gettimeofday(&philo->data->t_start, NULL);
	start = &philo->data->t_start;
	start->tv_sec += 1;
	start->tv_usec = 0;
	gettimeofday(&wait, NULL);
	my_usleep(time_conv(*start) - time_conv(wait), time_ts(wait), wait);
	if (philo->id % 2 == 0)
		my_usleep(philo->data->info[T_EAT] / 2, time_ts(*start), *start);
}

void	routine(t_philo	*philo)
{
	pthread_t	schrodinger;

	sync_start(philo);
	if (pthread_create(&schrodinger, NULL, &schrodinger_monitor, philo))
		exit(E_NEWTH);
	if (pthread_detach(schrodinger))
		exit(E_DETTH);
	while (true)
	{
		perform_routine(philo);
		print_status(philo, THINK);
	}
	exit(EXIT_SUCCESS);
}

static int	check_starvation(t_philo *philo)
{
	t_time	eat_limit;
	t_time	current;

	current = time_ts(philo->data->t_start);
	eat_limit = philo->hunger - current;
	if (eat_limit > 0)
	{
		my_usleep(eat_limit, current, philo->data->t_start);
		return (0);
	}
	print_status(philo, DEAD);
	exit(EXIT_SUCCESS);
}

void	*schrodinger_monitor(void *v_philo)
{
	t_philo			*philo;
	struct timeval	start;

	philo = (t_philo *)v_philo;
	start = philo->data->t_start;
	while (true)
	{
		if (philo->status != EAT)
			check_starvation(philo);
		else
			my_usleep(philo->data->info[EAT], time_ts(start), start);
	}
	return (NULL);
}
