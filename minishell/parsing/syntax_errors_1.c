/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:33:22 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/17 14:04:30 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redi_operator(t_tok_type type)
{
	return (type == TOK_REDIR_INPUT
		|| type == TOK_REDIR_OUTPUT
		|| type == TOK_REDIR_APPEND
		|| type == TOK_REDIR_HEREDOC);
}

int	open_quotes(char *str, int *i)
{
	int		k;
	char	quote;

	k = 0;
	if (str[*i] == '"' || str[*i] == '\'')
	{
		k = 1;
		quote = str[(*i)++];
		while (str[*i] && str[*i] != quote)
			(*i)++;
		if (str[*i] == quote)
		{
			k = 0;
			(*i)++;
		}
	}
	else
		(*i)++;
	return (k);
}

int	word_error(t_token *tmp)
{
	char	*str;
	int		i;
	int		k;

	i = 0;
	str = tmp->value;
	while (str[i])
		k = open_quotes(str, &i);
	if (k == 1)
	{
		ft_putstr_fd("minishell: syntax error \n", 2);
		exit_status(258, 0);
		return (1);
	}
	return (0);
}

void	max_herdoc(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == TOK_REDIR_HEREDOC)
			i++;
		token = token->next;
	}
	if (i > 16)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		exit(exit_status(2, 0));
	}
}
