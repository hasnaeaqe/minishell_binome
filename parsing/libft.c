/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:40:38 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/13 21:37:09 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
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
char	*ft_strdup1( const char *s1)
{
	int		lens1;
	int		i;
	char	*tab;

	lens1 = ft_strlen(s1);
	tab = malloc ((lens1 + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
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

int	ft_strchr(const char *s, int c)
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
char	*ft_strchr1(const char *s, int c)
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
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
char	*ft_strjoin(char  *s1, char  *s2)
{
	char	*newstr;
	char	*head;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	newstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) +1 * sizeof(char));
	if (!newstr)
		return (NULL);
	head = newstr;
	while (*s1)
		*newstr++ = *s1++;
	while (*s2)
		*newstr++ = *s2++;
	*newstr = '\0';
	return (head);
}
void	ft_strncpy(char *dest, char *src, int n)
{
	int i;
	i = 0;
	while(i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
char	*ft_my_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		k;
	size_t		max_copy;
	size_t		len_dst;

	len_dst = ft_strlen(dst);
	if (dstsize == 0 || len_dst >= dstsize)
		return (dst);
	max_copy = dstsize - len_dst - 1;
	k = 0;
	while (k < max_copy && src[k] != '\0')
	{
		dst[len_dst + k] = src[k];
		k++;
	}
	dst[len_dst + k] = '\0';
	return (dst);
}
