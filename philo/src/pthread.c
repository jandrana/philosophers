/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:17:43 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/12 20:24:02 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	start_threads(t_data *data)
{
	int			i;
	pthread_t	th_sup;
	void		*exec;

	exec = get_routine_to_execute(data);
	i = -1;
	while (++i < data->info[N_PHILOS])
	{
		if (pthread_create(&data->th->p_th[i], NULL, exec, &data->philos[i]))
			exit_philo(&data, E_NEWTH);
	}
	if (pthread_create(&th_sup, NULL, &greed_supervisor, data))
		exit_philo(&data, E_NEWTH);
	i = -1;
	while (!data->start)
		my_usleep(10);
	while (++i < data->info[N_PHILOS])
	{
		if (pthread_join(data->th->p_th[i], NULL))
			exit_philo(&data, E_DETTH);
	}
}
