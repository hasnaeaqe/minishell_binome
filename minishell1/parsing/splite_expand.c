/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:31:49 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/17 11:22:51 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_nodes1(t_token **tmp, t_token **prev,
	char *str, t_replace_ctx **ctx)
{
	char	*dest;
	t_token	*add;

	if ((*ctx)->i - (*ctx)->start <= 0)
		return ;
	dest = ft_substr(str, (*ctx)->start, (*ctx)->i - (*ctx)->start);
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
	t_replace_ctx **ctx, t_token **neext)
{
	char	*dest;
	t_token	*add;

	if ((*ctx)->i - (*ctx)->start <= 0)
		return ;
	dest = ft_substr((*ctx)->str, (*ctx)->start, (*ctx)->i - (*ctx)->start);
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
	t_replace_ctx	*ctx;
	char			*str;

	ctx = ft_malloc(sizeof(t_replace_ctx));
	*neext = (*tmp)->next;
	str = ft_strdup((*tmp)->value);
	ctx->str = str;
	ctx->i = 0;
	ctx->start = ctx->i;
	while (str[ctx->i])
	{
		if (str[ctx->i] == '\'' || str[ctx->i] == '"')
			skip_single_double_quote(str, &(ctx->i));
		else if (str[ctx->i] == ' ' || str[ctx->i] == '\0')
		{
			add_nodes1(tmp, prev, str, &ctx);
			if (str[ctx->i])
				ctx->start = ++ctx->i;
		}
		else
			ctx->i++;
	}
	add_nodes2(tmp, prev, &ctx, neext);
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
	handel_case(token);
}
