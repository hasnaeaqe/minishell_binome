/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:08:19 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/11 20:52:04 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tokens(t_token **token)
{
	t_token	*tmp;
	char	*str;
	char	*dest;
	int		i;
	int		j;
	int		start;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == TOK_WORD)
		{
			i = 0;
			j = 0;
			str = tmp->value;
			while (str[i])
			{
				if (str[i] == '"')
				{
					i++;
					while (str[i] != '"')
					{
						if (str[i] == '$')
						{
							start = ++i;
							while (str[i]!=' ' || str[i] != '|' || )
						}
						else
							dest[j++] = str[i];
					}
				}
			}
		}
	}
}
