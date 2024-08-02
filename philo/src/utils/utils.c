/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:11:50 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/02 16:53:03 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	ph_un_atol(char *str)
{
	long	i;
	long	j;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		return (E_NOTPOS);
	if (str[i] == '+')
		i++;
	j = i--;
	while (str[++i] >= '0' && str[i] <= '9' && result >= 0)
		result = result * 10 + (str[i] - '0');
	if (ft_strlen(str) > 19 || result < 0)
		return (E_OORL);
	if (str[i] || j == i)
		return (E_NAN);
	return (result);
}

int	array_len(char **array)
{
	int	len;

	len = -1;
	while (array[++len])
		;
	return (len);
}

bool	in_range(ssize_t value, ssize_t min, ssize_t max)
{
	if (value >= min && value <= max)
		return (0);
	return (1);
}
