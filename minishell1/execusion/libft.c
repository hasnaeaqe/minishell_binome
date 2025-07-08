/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:21:35 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/08 20:40:08 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// static void	check_atoi(int signe, long long c)
// {
// 	if ((signe == 1 && c > INT_MAX) || (signe == -1 && (-c) < INT_MIN))
// 	{
// 		printf("error");
// 	}
// }

long	ft_atoi( char *str, int *overflow)
{
	int			i;
	long long	c;
	int			signe;

	i = 0;
	c = 0;
	signe = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		if ((c > (LONG_MAX / 10)) ||
			(c == (LONG_MAX / 10) && (*str - '0') > (LONG_MAX % 10)))
		{
			*overflow = 1;
			return (0);
		}
		c = c * 10 + (str[i] - '0');
		// if ((signe == 1 && c > INT_MAX) || (signe == -1 && (-c) < INT_MIN))
		// 	return ((long)(c * signe));
		i++;
	}
	return ((signe * c));
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

void	ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
