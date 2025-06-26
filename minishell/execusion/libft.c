/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:21:35 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/26 16:05:42 by haqajjef         ###   ########.fr       */
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

long	ft_atoi( char *str)
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
	while (str[i] >= '0' && str[i] <= '9')
	{
		c = c * 10 + (str[i] - '0');
		if ((signe == 1 && c > INT_MAX) || (signe == -1 && (-c) < INT_MIN))
			return ((long)(c * signe));
		i++;
	}
	return ((long)(signe * c));
}

// size_t ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }
// char	*ft_strdup( const char *s1)
// {
// 	int		lens1;
// 	int		i;
// 	char	*tab;

// 	lens1 = ft_strlen(s1);
// 	tab = malloc ((lens1 + 1) * sizeof(char));
// 	if (tab == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		tab[i] = s1[i];
// 		i++;
// 	}
// 	tab[i] = '\0';
// 	return (tab);
// }

// char	*ft_strjoin(char  *s1, char  *s2)
// {
// 	char	*newstr;
// 	char	*head;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_strdup(s2));
// 	if (!s2)
// 		return (ft_strdup(s1));
// 	newstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) +1 * sizeof(char));
// 	if (!newstr)
// 		return (NULL);
// 	head = newstr;
// 	while (*s1)
// 		*newstr++ = *s1++;
// 	while (*s2)
// 		*newstr++ = *s2++;
// 	*newstr = '\0';
// 	return (head);
// }
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
	int i;
	i = 0;
	while(i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}