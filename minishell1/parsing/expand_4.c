/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:05:05 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/12 16:09:34 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	loop_rwina(t_replace_ctx *ctx,
	char **total_str, size_t flag, size_t *j)
{
	size_t	i;
	size_t	dest_len;

	i = 0;
	dest_len = ft_strlen(ctx->dest);
	while (ctx->value[i])
	{
		if (ctx->value[i] == '\'' && flag == 0)
			replace_single_quote(&i, j, ctx->value, total_str);
		else if (ctx->value[i] == '"')
			replace_double_quote(&i, j, total_str, ctx);
		else if (ctx->value[i] == '$' && ctx->value[i + 1]
			&& (ft_strncmp(&(ctx->value)[i + 1], ctx->dest, dest_len) == 0
			|| ft_strncmp(&(ctx->value)[i], ctx->dest, dest_len) == 0
			|| (ctx->value)[i + 1] == ctx->dest[0] * (-1)))
			replace_word(&i, j, total_str, ctx);
		else
		{
			puts("2");
			(*total_str)[(*j)++] = ctx->value[i++];
		}
	}
}

char	*rwina(t_replace_ctx *ctx, size_t len, int flag)
{
	char		*total_str;
	size_t		j;

	total_str = ft_malloc((len + 1) * sizeof(char));
	j = 0;
	loop_rwina(ctx, &total_str, flag, &j);
	if (!total_str)
		return (NULL);
	total_str[j] = '\0';
	return (total_str);
}

t_redir_node	*new_redir(t_redir_type kind,
	char *filename, int flag, int ambiguous)
{
	t_redir_node	*new;

	new = ft_malloc(sizeof(t_redir_node));
	new->kind = kind;
	new->filename = trasform_garbeg(rm_quotes(filename));
	new->flag = flag;
	new->ambiguous = ambiguous;
	new->next = NULL;
	return (new);
}

t_token	*new_token(t_tok_type type, char *value)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token));
	new->type = type;
	new->ambig = 0;
	new->value = ft_strdup(value);
	if (!new)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

int	handel_ambiguous(t_token **token)
{
	t_token	*tmp;

	if (!token || !*token)
		return (1);
	tmp = *token;
	while (tmp)
	{
		if (tmp->type == TOK_REDIR_APPEND || tmp->type == TOK_REDIR_INPUT
			|| tmp->type == TOK_REDIR_OUTPUT)
		{
			if (tmp->next && count_word(tmp->next->value, ' ') != 1)
			{
				tmp->ambig = 1;
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
