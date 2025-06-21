/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:40:38 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/19 16:11:19 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	str = (char *)ft_malloc((i + 1) * sizeof(char));
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strndup(const char *s1,int n)
{
	char	*str;
	int		i;

	i = 0;
	while (s1[i] != '\0' && i < n)
		i++;
	str = (char *)ft_malloc((i + 1) * sizeof(char));
	i = 0;
	while (s1[i] != '\0' && i < n)
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

int	ft_strcmp(const char *s1,const char *s2)
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

int	ft_stchr(const char *s, int c)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			count++;
		i++;
	}
	return (count);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*l;

	s = (unsigned char *)s1;
	l = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s[i] == l[i] && i < n)
	{
		if (s[i] == '\0' || l[i] == '\0')
			return (0);
		i++;
	}
	if (i < n)
		return (s[i] - l[i]);
	return (0);
}