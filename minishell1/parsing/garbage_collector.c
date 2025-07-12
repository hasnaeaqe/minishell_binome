/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:53:14 by cbayousf          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/12 13:19:19 by haqajjef         ###   ########.fr       */
=======
/*   Updated: 2025/07/12 16:22:05 by cbayousf         ###   ########.fr       */
>>>>>>> 712bc4be0111533d6c44bc842618b5273d222d11
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free(void *p, size_t k)
{
	static void		*lst[1000000]; //INT_MAX+
	static size_t	i;

	// while(i > 0 ) free(lst[--i])
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
