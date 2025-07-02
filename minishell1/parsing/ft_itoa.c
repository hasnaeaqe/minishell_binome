/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:27:09 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/27 10:27:10 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

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