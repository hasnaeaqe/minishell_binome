/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:21:35 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/20 12:31:58 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	check_overflow(long long prev, long long current, int *overflow)
{
	if (current / 10 != prev)
	{
		*overflow = 1;
		return (1);
	}
	return (0);
}

long	ft_atoi(char *str, int *overflow)
{
	int			i;
	long long	c;
	long long	prev;
	int			signe;

	i = 0;
	c = 0;
	signe = 1;
	while (str && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		prev = c;
		c = c * 10 + (str[i] - '0');
		if (check_overflow(prev, c, overflow))
			return (0);
		i++;
	}
	return (signe * c);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
