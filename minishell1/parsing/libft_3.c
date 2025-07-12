/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:39:33 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/10 16:31:01 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_word(char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i])
			{
				if (s[i] == '"' || s[i] == '\'')
					skip_single_double_quote(s, &i);
				else
					i++;
			}
		}
	}
	return (count);
}

char	*ft_strjoin(char *s1, char *s2)
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

static int	ft_count_nbr(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n == 0)
		i++;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static void	trans(char *s, int nbr, int len)
{
	s[len] = '\0';
	if (nbr == 0)
	{
		s [0] = '0';
		return ;
	}
	if (nbr < 0)
	{
		s[0] = '-';
		if (nbr == -2147483648)
		{
			s[--len] = '8';
			nbr = -(nbr / 10);
		}
		else
			nbr = -nbr;
	}
	while (nbr > 0)
	{
		s[--len] = (nbr % 10) + '0';
		nbr = (nbr / 10);
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_count_nbr(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	trans(str, n, len);
	return (str);
}
