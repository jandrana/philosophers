/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:34:13 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/08 21:01:44 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_input(t_data *data)
{
	printf("[N PHILOS/FORKS]= %i\n", data->info[N_PHILOS]);
	printf("[TIME_TO_DIE]= %i\n", data->info[T_DIE]);
	printf("[TIME_TO_EAT]= %i\n", data->info[T_EAT]);
	printf("[TIME_TO_SLEEP]= %i\n", data->info[T_SLEEP]);
	printf("[TIMES_EACH_PHILO_MUST_EAT]= %i\n", data->info[NT_EAT]);
}

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
	uint64_t	timestamp;

	pthread_mutex_lock(&wise_man->data->lock);
	timestamp = time_ms(wise_man->data->start);
	if (action == DEAD)
		printf("%lu %i %s", timestamp, wise_man->id, O_DEAD);
	else if (action != DEAD && !wise_man->data->stop)
		printf("%lu %i %s", timestamp, wise_man->id, get_action_msg(action));
	pthread_mutex_unlock(&wise_man->data->lock);
}
