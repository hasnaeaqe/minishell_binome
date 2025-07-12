/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:40:34 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/12 16:09:14 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_value(size_t *i, char *str)
{
	size_t	j;
	char	*dest;

	j = 0;
	if (j == (*i) - 1)
	{
		if (str[*i] != '"' && str[*i] != '\'')
		{
			dest = ft_malloc((*i + 2) * sizeof(char));
			dest[j++] = str[*i - 1];
			dest[j++] = str[*i];
		}
		else
		{
			dest = ft_malloc((*i + 1) * sizeof(char));
			dest[j++] = str[*i] * (-1);
		}
	}
	else
	{
		dest = ft_malloc((*i + 1) * sizeof(char));
		while (j < *i - 1)
		{
			dest[j] = str[j + 1];
			j++;
		}
	}
	dest[j] = '\0';
	return (dest);
}

static char	*find_expand(char *str)
{
	size_t		i;
	size_t		j;
	char		*dest;

	i = 1;
	j = 0;
	if (!str || str[0] != '$' )
		return (NULL);
	if (str[1] == '?')
		return (ft_strdup("?"));
	if (ft_isdigit(str[i]))
	{
		dest = ft_malloc(2 * sizeof(char));
		dest[j++] = str[i];
		dest[j] = '\0';
		return (dest);
	}
	while (str[i]
		&& (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
		i++;
	return (expand_value(&i, str));
}

static char	*extract_value(char *dest, t_env *env)
{
	if (!dest)
		return (NULL);
	if (ft_strcmp(dest, "?") == 0)
		return (ft_itoa(exit_status(0, 1)));
	while (env)
	{
		if (ft_strcmp(env->key, dest) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	if (ft_strchr(dest, '$') || !ft_isascii(dest[0]))
		return (ft_strdup(dest));
	return (NULL);
}

static char	*transform_to_gar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = ' ';
		else if (str[i] == '\t')
			str[i] = ' ';
		else
			str[i] = str[i] * (-1);
		i++;
	}
	return (str);
}

char	*expand(char *src, char *str, t_env *env, int flag)
{
	t_replace_ctx	*ctx;
	size_t			len;
	size_t			count;

	ctx = ft_malloc(sizeof(t_replace_ctx));
	ctx->value = src;
	ctx->dest = find_expand(str);
	ctx->expand_value = transform_to_gar(extract_value(ctx->dest, env));
	count = count_expand(src, ctx->dest, flag);
	len = ft_strlen(src) - ft_strlen(ctx->dest) * count
		+ ft_strlen(ctx->expand_value) * count ;
	return (rwina(ctx, len, flag));
}
