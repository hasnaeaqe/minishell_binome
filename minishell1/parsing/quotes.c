/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:02:12 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/08 10:06:34 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_quote(char *src)
{
	int		i;
	char	quote;

	i = 0;
	while (src[i])
	{
		if ((src[i] == '\'' || src[i] == '"'))
		{
			quote = src[i++];
			while (src[i] == quote)
				i++;
			if (src[i] == '\0')
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

static char	*rm_qts(char *src, int len)
{
	char	*dest;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (count_quote(src) == 1)
		return (src);
	dest = ft_malloc((len + 1) * sizeof(char));
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '"')
		{
			quote = src[i++];
			while (src[i] && src[i] != quote)
				dest[j++] = src[i++];
			if (src[i] == quote)
				i++;
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
	return (dest);
}

static int	quote_loop(char *src, int *i)
{
	char	quote;
	int		len;

	len = 0;
	if (src[*i] == '\'' || src[*i] == '"')
	{
		quote = src[(*i)++];
		while (src[*i] && src[*i] != quote)
		{
			len++;
			(*i)++;
		}
		if (src[*i] == quote)
			(*i)++;
	}
	else
	{
		len++;
		(*i)++;
	}
	return (len);
}

static int	flag_heredoc(t_token *tmp)
{
	int	flag;

	flag = 0;
	if (ft_strchr(tmp->next->value, '\'') || ft_strchr(tmp->next->value, '"'))
		flag = 1;
	return (flag);
}

int	remove_quotes(t_token **token)
{
	t_token	*tmp;
	char	*src;
	int		len;
	int		i;
	int		flag;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == TOK_REDIR_HEREDOC)
			flag = flag_heredoc(tmp);
		if (tmp->type == TOK_WORD)
		{
			src = ft_strdup(tmp->value);
			i = 0;
			len = 0;
			while (src[i])
				len += quote_loop(src, &i);
			free(tmp->value);
			tmp->value = rm_qts(src, len);
		}
		tmp = tmp->next;
	}
	return (flag);
}
