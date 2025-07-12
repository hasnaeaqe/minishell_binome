/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:48:12 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/12 16:06:19 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_export(t_token *token)
{
	char	*str;
	t_token	*tmp;
	int		i;
	int		check;

	if (!token)
		return ;
	tmp = token;
	if (ft_strcmp(tmp->value, "export") == 0 && tmp->next)
	{
		tmp = tmp->next;
		while (tmp)
		{
			if (tmp->type == TOK_WORD)
			{
				str = ft_strdup(tmp->value);
				i = 0;
				check = valide_key(str, &i);
				if (check == 0 && !ft_strchr(&str[i], '"')
					&& !ft_strchr(&str[i], '\''))
					tmp->value = add_quotes(str);
			}
			tmp = tmp->next;
		}
	}
}

void	replace_single_quote(size_t *i, size_t *j,
	char *value, char **total_str)
{
	(*total_str)[(*j)++] = value[(*i)++];
	while (value[*i] && value[*i] != '\'')
		(*total_str)[(*j)++] = value[(*i)++];
	if (value[*i] == '\'')
		(*total_str)[(*j)++] = value[(*i)++];
}

void	check_if_condition(t_replace_ctx *ctx, char **total_str, size_t *j)
{
	size_t	k;

	k = 0;
	if (ctx->expand_value != NULL)
	{
		while (ctx->expand_value[k])
			(*total_str)[(*j)++] = ctx->expand_value[k++];
	}
}

void	replace_double_quote(size_t *i, size_t *j,
	char **total_str, t_replace_ctx *ctx)
{
	size_t	dest_len;

	dest_len = ft_strlen(ctx->dest);
	(*total_str)[(*j)++] = ctx->value[(*i)++];
	while (ctx->value[*i] && ctx->value[*i] != '"')
	{
		if (ctx->value[*i] == '$' && ctx->value[*i + 1]
			&& (ft_strncmp(&ctx->value[*i + 1], ctx->dest, dest_len) == 0
				|| ft_strncmp(&ctx->value[*i], ctx->dest, dest_len) == 0
				|| (ctx->value)[*i + 1] == ctx->dest[0] * (-1)))
		{
			check_if_condition(ctx, total_str, j);
			if (ft_strncmp(&ctx->value[*i], ctx->dest, dest_len) == 0)
				*i += dest_len;
			else
				*i += dest_len + 1;
		}
		else
			(*total_str)[(*j)++] = ctx->value[(*i)++];
	}
	if (ctx->value[*i] == '"')
		(*total_str)[(*j)++] = ctx->value[(*i)++];
}

void	replace_word(size_t *i, size_t *j, char **total_str, t_replace_ctx *ctx)
{
	size_t	k;

	k = 0;
	if (ctx->expand_value != NULL)
	{
		while (ctx->expand_value[k])
			(*total_str)[(*j)++] = ctx->expand_value[k++];
	}
	if (ft_strncmp(&(ctx->value)[*i], ctx->dest, ft_strlen(ctx->dest)) == 0)
		(*i) += ft_strlen(ctx->dest);
	else
		(*i) += ft_strlen(ctx->dest) + 1;
}
