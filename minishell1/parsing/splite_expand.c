/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:31:49 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/15 14:05:30 by cbayousf         ###   ########.fr       */
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

static void	add_nodes2(t_token **tmp, t_token **prev, char *str,
	t_replace_ctx **ctx, t_token **neext)
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
	add_nodes2(tmp, prev, str, &ctx, neext);
	if (*neext)
		(*prev)->next = *neext;
}

// int	quote_h(char *src)
// {
// 	int		i = 0;
// 	char	curr;
// 	int		switch_count = 0;

// 	if (!src[i])
// 		return (0);
// 	if (src[i]==' ')
// 	{
// 		while (src[i]==' ')
// 			i++;
// 		if (src[i]=='\0')
// 			return (1);
// 	}
// 	if (src[i] != '\'' && src[i] != '"')
// 		return (0);

// 	curr = src[i];

// 	while (src[i])
// 	{
// 		if (src[i] != '\'' && src[i] != '"')
// 			return (0);

// 		if (src[i] != curr)
// 		{
// 			switch_count++;
// 			curr = src[i];
// 			if (switch_count > 1)
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }
// int space_h(char *src)
// {
// 	int i =0;
// 	if (src[i]==' ')
// 	{
// 		while (src[i]==' ')
// 			i++;
// 		if (src[i]=='\0')
// 			return (1);
// 	}
// 	return (0);
// }

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
	handel_chihaja(token);
}
