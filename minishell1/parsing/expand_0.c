/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:08:19 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/08 12:40:12 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_single_quote(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'' && (*i) != 0)
		(*i)++;
}

static void	expand_double_quote(char **str, int *i, t_env *env)
{
	(*i)++;
	while ((*str)[*i] && (*str)[*i] != '"')
	{
		if ((*str)[*i] == '$' && (*str)[*i + 1] && (*str)[*i + 1] == '"')
			(*i) += 2;
		else if ((*str)[*i] == '$' && (*str)[*i + 1])
		{
			(*str) = expand((*str), &(*str)[*i], env, 0);
			*i = 0;
			break ;
		}
		else
			(*i)++;
	}
	if ((*str)[*i] == '"' && (*i) != 0)
		(*i)++;
}

static void	check_while(char **str, int *i, t_env *env)
{
	if ((*str)[*i] == '\'')
		expand_single_quote(*str, i);
	else if ((*str)[*i] == '"')
		expand_double_quote(str, i, env);
	else if ((*str)[*i] == '$' && (*str)[(*i) + 1])
	{
		*str = expand(*str, &(*str)[*i], env, 0);
		*i = 0; 
	}
	else
		(*i)++;
}

void	expand_tokens(t_token **token, t_env *env)
{
	t_token	*tmp;
	t_token	*prev;
	char	*str;
	int		i;

	tmp = *token;
	prev = *token;
	check_export(tmp);
	while (tmp)
	{
		if (tmp->type == TOK_WORD && prev->type != TOK_REDIR_HEREDOC)
		{
			str = ft_strdup(tmp->value);
			i = 0;
			while (str[i])
				check_while(&str, &i, env);
			free(tmp->value);
			tmp->value = str;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

char	*expand_heredoc(char *line, t_env *env, int flag)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
			line = expand(line, &line[i], env, flag);
		else
			i++;
	}
	return (line);
}
