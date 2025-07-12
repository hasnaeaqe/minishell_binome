/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:02:12 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/12 12:29:55 by cbayousf         ###   ########.fr       */
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
			if (src[i] == '\0' )
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

static char	*rm_qts(char *src, size_t len)
{
	char		*dest;
	char		quote;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
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
	int		flag;

	if (!token || !*token)
		return (0);
	tmp = *token;
	while (tmp)
	{
		if (tmp->type == TOK_REDIR_HEREDOC)
			flag = flag_heredoc(tmp);
		tmp = tmp->next;
	}
	return (flag);
}

char	*rm_quotes(char *src)
{
	size_t	i;
	size_t	len;
	char	quote;

	i = 0;
	len = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '"')
		{
			quote = src[i++];
			while (src[i] && src[i] != quote)
			{
				len++;
				i++;
			}
			if (src[i] == quote)
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (rm_qts(src, len));
}
