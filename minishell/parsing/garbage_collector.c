/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:53:14 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/19 20:42:30 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(void *p, int k)
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

void	ft_exit(size_t n)
{
	ft_free(NULL, 1);
	exit(n);
}

void	*ft_malloc(size_t i)
{
	void	*k;

	k = malloc(i);
	i = 0;
	if (!k)
		ft_exit(1);
	ft_free(k, 0);
	return (k);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

char	*trasform_garbeg(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			str[i] = str[i] * (-1);
		i++;
	}
	return (str);
}
