/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:44:40 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/14 12:50:16 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(const char *str, ssize_t start, ssize_t len)
{
	char	*substr;
	int		i;

	if (start >= ft_strlen(str))
		return (NULL);
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = -1;
	while (str[++i + start] && --len + 1)
		substr[i] = str[i + start];
	substr[i] = '\0';
	return (substr);
}

long	ft_atoui(char *str)
{
	int			i;
	int			j;
	int			neg;
	long		result;

	i = 0;
	neg = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-' && ++i)
		neg = -1;
	j = --i;
	while (str[++j] >= '0' && str[j] <= '9')
		;
	if (str[j] || j == i)
		return (E_NAN);
	while (str[++i] && result >= 0 && result <= INT_MAX)
		result = result * 10 + (str[i] - '0');
	result *= neg;
	if ((result > INT_MAX) || result < INT_MIN)
		return (E_OORL);
	return (result);
}
