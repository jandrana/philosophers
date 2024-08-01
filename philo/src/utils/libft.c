/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:44:40 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/01 13:28:58 by ana-cast         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*result;
	int		len_s1;
	int		len_s2;

	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	i = len_s1 + len_s2;
	result = (char *)malloc(sizeof(char) * i + 1);
	if (result == NULL)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		result[i] = s1[i];
	i = -1;
	while (++i < len_s2)
		result[i + len_s1] = s2[i];
	result[i + len_s1] = '\0';
	return (result);
}
