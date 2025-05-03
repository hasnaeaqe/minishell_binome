/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:53:14 by cbayousf          #+#    #+#             */
/*   Updated: 2025/05/02 13:53:46 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static void	ft_free(void *p, int k)
{
	static void		*lst[INT_MAX];
	static size_t	i;

	if (k)
	{
		while (lst[i])
			free(lst[i--]);
	}
	else
		lst[i++] = p;
}

void	ft_exit(int n)
{
	ft_free(NULL, 1);
	exit(n);
}

void	*ft_malloc(size_t i)
{
	void	*k;

	k = malloc(i);
	if (!k)
		ft_exit(1);
	ft_free(k, 0);
	return (k);
}
