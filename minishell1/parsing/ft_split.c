/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:01:05 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/10 13:09:34 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
		{
			i++;
		}
		if (s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static char	*ft_ndup(const char *s1, int n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((n + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[n] = '\0';
	return (str);
}

static void	ft_free(char **t, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(t[i]);
		i++;
	}
	free(t);
}

static char	**cr_word(char const *s, char c, char **result)
{
	int	i;
	int	d;
	int	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		d = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		result[k] = ft_ndup(s + d, i - d);
		if (result[k] == NULL)
		{
			ft_free(result, k);
			return (NULL);
		}
		k++;
	}
	result[k] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	// int		i;
	// int		k;

	// i = 0;
	// k = 0;
	if (s == NULL)
		return (NULL);
	result = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = cr_word(s, c, result);
	return (result);
}
