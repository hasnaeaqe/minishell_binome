/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:33:22 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/07 15:50:51 by cbayousf         ###   ########.fr       */
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
