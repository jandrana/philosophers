/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:34:13 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/12 20:22:15 by ana-cast         ###   ########.fr       */
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
