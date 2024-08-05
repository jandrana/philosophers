/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:44:40 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/05 17:40:04 by ana-cast         ###   ########.fr       */
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

void	philo_strcpy(char *dst, const char *src, int len)
{
	while (*src && --len)
		*dst++ = *src++;
	*dst = '\0';
}

char	*ft_strdup(char *str)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	return (philo_strcpy(dup, str, 0), dup);
}

char	*ft_substr(const char *str, ssize_t start, ssize_t len)
{
	char	*substr;

	if (start >= ft_strlen(str))
		return (NULL);
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	philo_strcpy(substr, str + start, len + 1);
	return (substr);
}

long long	ft_atoul(char *str)
{
	int			i;
	int			j;
	long long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (E_NOTPOS);
	j = i--;
	while (str[++i] >= '0' && str[i] <= '9' && result >= 0)
	{
		result = result * 10 + (str[i] - '0');
		if ((result > UINT32_MAX))
			return (E_OORL);
	}
	if (str[i] || j == i)
		return (E_NAN);
	if (!result)
		return (E_NOTPOS);
	return (result);
}
