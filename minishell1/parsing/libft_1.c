/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:40:38 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/13 10:12:11 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char		*str;
	size_t		i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	str = (char *)ft_malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strndup(char *s1, size_t n)
{
	char		*str;
	size_t		i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && i < n)
		i++;
	str = (char *)ft_malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*l;

	s = (unsigned char *)s1;
	l = (unsigned char *)s2;
	i = 0;
	while (s[i] == l[i])
	{
		if (s[i] == '\0' || l[i] == '\0')
			return (0);
		i++;
	}
	return (s[i] - l[i]);
}
