/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:32:06 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/19 20:40:09 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_token(t_token **token, t_tok_type type, char *value)
{
	t_token	*tmp;
	t_token	*new;

	new = new_token(type, value);
	if (!token || !new)
		return ;
	if (!*token)
		*token = new;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static void	tok_redir_1(size_t *i, t_token **token, char *str)
{
	if (str[*i + 1] == '<')
	{
		add_token(token, TOK_REDIR_HEREDOC, "<<");
		*i += 2;
	}
	else
	{
		add_token(token, TOK_REDIR_INPUT, "<");
		(*i)++;
	}
}

static void	tok_redir_2(size_t *i, t_token **token, char *str)
{
	if (str[*i + 1] == '>')
	{
		add_token(token, TOK_REDIR_APPEND, ">>");
		*i += 2;
	}
	else
	{
		add_token(token, TOK_REDIR_OUTPUT, ">");
		(*i)++;
	}
}

static void	tok_word(size_t *i, t_token **token, char *str)
{
	int		start;
	char	*word_quote;
	char	quote;

	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '|'
		&& str[*i] != '<' && str[*i] != '>')
	{
		if (str[*i] == '\t')
			str[*i] = ' ';
		else if (str[*i] == '\'' || str[*i] == '"')
		{
			quote = str[(*i)++];
			while (str[*i] && str[*i] != quote)
				(*i)++;
			if (str[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	word_quote = ft_strndup(&str[start], *i - start);
	add_token(token, TOK_WORD, word_quote);
}

void	tokenisation(char *str, t_token **token)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (!str[i])
			return ;
		if (str[i] == '|')
		{
			add_token(token, TOK_PIPE, "|");
			i++;
		}
		else if (str[i] == '<')
			tok_redir_1(&i, token, str);
		else if (str[i] == '>')
			tok_redir_2(&i, token, str);
		else
			tok_word(&i, token, str);
	}
}
