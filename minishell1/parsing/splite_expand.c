/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:31:49 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/12 12:24:41 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_nodes1(t_token **tmp, t_token **prev,
	char *str, int *start, int *i)
{
	char	*dest;
	t_token	*add;

	dest = ft_substr(str, *start, (*i) - (*start));
	add = new_token(TOK_WORD, dest);
	if (!*prev)
	{
		free((*tmp)->value);
		(*tmp)->value = ft_strdup(dest);
		*prev = *tmp;
	}
	else
	{
		(*prev)->next = add;
		*prev = (*prev)->next;
		*tmp = *prev;
	}
}

static void	add_nodes2(t_token **tmp, t_token **prev,
	char *str, int *start, int *i, t_token **neext)
{
	char	*dest;
	t_token	*add;

	dest = ft_substr(str, *start, (*i) - (*start));
	add = new_token(TOK_WORD, dest);
	if (!*prev)
	{
		free((*tmp)->value);
		(*tmp)->value = ft_strdup(dest);
		*prev = *tmp;
	}
	else
	{
		(*prev)->next = add;
		*prev = (*prev)->next;
		(*prev)->next = *neext;
		*tmp = *prev;
	}
}

void	skip_single_double_quote(char *str, int *i)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
}

static void	loop_split(t_token **neext, t_token **tmp, t_token **prev)
{
	int		start;
	int		i;
	char	*str;

	*neext = (*tmp)->next;
	str = ft_strdup((*tmp)->value);
	i = 0;
	start = i;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_single_double_quote(str, &i);
		else if (str[i] == ' ' || str[i] == '\0')
		{
			add_nodes1(tmp, prev, str, &start, &i);
			if (str[i])
				start = ++i;
		}
		else
			i++;
	}
	add_nodes2(tmp, prev, str, &start, &i, neext);
	if (*neext)
		(*prev)->next = *neext;
}

void	splite_expand(t_token **token)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*neext;

	if (!token || !*token)
		return ;
	tmp = *token;
	prev = NULL;
	neext = NULL;
	while (tmp)
	{
		if (tmp->type == TOK_WORD)
		{
			if (ft_strchr(tmp->value, ' '))
				loop_split(&neext, &tmp, &prev);
			else
				prev = tmp;
		}
		else
			prev = tmp;
		tmp = tmp->next;
	}
}
