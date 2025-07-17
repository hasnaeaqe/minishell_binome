/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:32:53 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/17 11:21:51 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	loop_in_while(char *src, int *i, char *curr, int *switch_count)
{
	while (src[*i])
	{
		if (src[*i] != '\'' && src[*i] != '"')
			return (0);
		if (src[*i] != *curr)
		{
			(*switch_count)++;
			*curr = src[*i];
			if (*switch_count > 1)
				return (0);
		}
		(*i)++;
	}
	return (1);
}

int	quote_h(char *src)
{
	int		i;
	char	curr;
	int		switch_count;

	i = 0;
	switch_count = 0;
	if (!src[i])
		return (0);
	if (src[i] == ' ')
	{
		while (src[i] == ' ')
			i++;
		if (src[i] == '\0')
			return (1);
	}
	if (src[i] != '\'' && src[i] != '"')
		return (0);
	curr = src[i];
	if (loop_in_while(src, &i, &curr, &switch_count) == 0)
		return (0);
	return (1);
}

int	space_h(char *src)
{
	int	i;

	i = 0;
	if (src[i] == ' ')
	{
		while (src[i] == ' ')
			i++;
		if (src[i] == '\0')
			return (1);
	}
	return (0);
}

void	split_nodes(t_token **prev, t_token **token,
	t_token **tmp, t_token **next)
{
	if (!*prev)
		*token = *next;
	else
		(*prev)->next = *next;
	free((*tmp)->value);
	free(*tmp);
	*tmp = *next;
}

void	handel_case(t_token **token)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*next;

	if (!token || !*token)
		return ;
	tmp = *token;
	prev = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (is_redi_operator(tmp->type))
			tmp = tmp->next->next;
		else if (tmp->type == TOK_WORD && (next || prev)
			&& quote_h(tmp->value) == 1)
			split_nodes(&prev, token, &tmp, &next);
		else if (!prev && !next && space_h(tmp->value) == 1)
			split_nodes(&prev, token, &tmp, &next);
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
