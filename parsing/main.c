/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:32:06 by cbayousf          #+#    #+#             */
/*   Updated: 2025/05/13 20:26:52 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*type_token(t_tok_type type)
{
	if (type == TOK_WORD)
		return ("WORD");
	else if (type == TOK_PIPE)
		return ("PIPE");
	else if (type == TOK_REDIR_INPUT)
		return ("REDIR_IN");
	else if (type == TOK_REDIR_OUTPUT)
		return ("REDIR_OUT");
	else if (type == TOK_REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (type == TOK_REDIR_HEREDOC)
		return ("REDIR_HEREDOC");
	else
		return ("UNKNOWN");
}

void	print_tokens(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("type : %s | value : %s\n", type_token(tmp->type), tmp->value);
		tmp = tmp->next;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

t_token	*new_token(t_tok_type type, char *value)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token));
	new->type = type;
	new->value = ft_strdup(value);
	if (!new)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	add_token(t_token **token, t_tok_type type, char *value)
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

void	tokenisation(char *str, t_token **token)
{
	int		start;
	char	*word_quote;
	char	quote;
	int		i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (!str[i])
			return ;
		if (str[i] == '|')
		{
			add_token(token, TOK_PIPE, "|");
			i++;
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] == '<')
			{
				add_token(token, TOK_REDIR_HEREDOC, "<<");
				i += 2;
			}
			else
			{
				add_token(token, TOK_REDIR_INPUT, "<");
				i++;
			}
		}
		else if (str[i] == '>')
		{
			if (str[i + 1] == '>')
			{
				add_token(token, TOK_REDIR_APPEND, ">>");
				i += 2;
			}
			else
			{
				add_token(token, TOK_REDIR_OUTPUT, ">");
				i++;
			}
		}
		else
		{
			start = i;
			if (str[i] == '\'' || str[i] == '"')
			{
				quote = str[i];
				while (str[i] && str[i] != quote)
					i++;
			}
			while (str[i] && str[i] != ' ' && str[i] != '|'
				&& str[i] != '<' && str[i] != '>')
			{
				if (str[i] == '\'' || str[i] =='"')
				{
					quote = str[i++];
					while (str[i] && str[i] != quote)
						i++;
					i++;
				}
				else
					i++;
			}
			word_quote = ft_strndup(&str[start], i - start);
			add_token(token, TOK_WORD, word_quote);
		}
	}
}

void f(void)
{
	system("leaks minishell");
}

int	main(void)
{
	char	*line;
	t_token	*token;
	t_tree	*tree;

	atexit(f);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		token = NULL;
		tokenisation(line, &token);
		print_tokens(token);
		if (check_syntax_errors(token))
		{
			free_tokens(token);
			free(line);
			continue ;
		}
		//expand_tokens(&token);
		tree = parse_tree(&token);
		print_tree(tree, 0);
		free_tokens(token);
		free(line);
	}
	return (0);
}
