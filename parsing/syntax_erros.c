/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_erros.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:22:59 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/12 11:44:02 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redi_operator(t_tok_type type)
{
	return (type == TOK_REDIR_INPUT
		|| type == TOK_REDIR_OUTPUT
		|| type == TOK_REDIR_APPEND
		|| type == TOK_REDIR_HEREDOC);
}

int	check_syntax_errors(t_token *token)
{
	t_token	*prev;
	t_token	*tmp;
	char *str;
	char quote;
	int i;
	int k;

	prev = NULL;
	tmp = token;
	while (tmp)
	{
		if (is_redi_operator(tmp->type))
		{
			if (!tmp->next || tmp->next->type != TOK_WORD)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				if (tmp->next)
					ft_putstr_fd(tmp->next->value, 2);
				else
					ft_putstr_fd("newline", 2);
				ft_putstr_fd("'\n", 2);
				return (1);
			}
		}
		if (tmp->type == TOK_PIPE)
		{
			if (!prev || prev->type == TOK_PIPE || is_redi_operator(prev->type))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				return (1);
			}
			if (!tmp->next || tmp->next->type == TOK_PIPE
				|| is_redi_operator(tmp->next->type))
			{
				if (!tmp->next)
					ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				else if (is_redi_operator(tmp->next->type))
				{
					if (!tmp->next->next || tmp->next->next->type != TOK_WORD)
					{
						ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
						if (tmp->next->next)
							ft_putstr_fd(tmp->next->next->value, 2);
						else
							ft_putstr_fd("newline", 2);
						ft_putstr_fd("'\n", 2);
						return (1);
					}
				}
				else
					ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				return (1);
			}
		}
		// if (ft_strcmp(tmp->value, "!") == 0)
		// {
		// 	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		// 	return (1);
		// }
		// if (ft_strncmp(tmp->value, ";", 1) == 0)
		// {
		// 	if (ft_strncmp(tmp->value, ";;", 2) == 0)
		// 		ft_putstr_fd("minishell: syntax error near unexpected token `;;'\n", 2);
		// 	else
		// 		ft_putstr_fd("minishell: syntax error near unexpected token `;'\n", 2);
		// 	return (1);
		// }
		// if (ft_strncmp(tmp->value, "&", 1) == 0)
		// {
		// 	if (ft_strncmp(tmp->value, "&&", 2) == 0)
		// 		ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
		// 	else
		// 		ft_putstr_fd("minishell: syntax error near unexpected token `&'\n", 2);
		// 	return (1);
		// }
		// if (ft_strncmp(tmp->value, "(", 1) == 0
		// 	|| ft_strncmp(tmp->value, ")", 1) == 0)
		// {
		// 	ft_putstr_fd("minishell: syntax error near unexpected token `)'\n", 2);
		// 	return (1);
		// }
		i = 0;
		k = 0;
		str = tmp->value;
		while (str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				k=1;
				quote = str[i++];
				while (str[i] && str[i] != quote)
					i++;
				if (str[i]==quote)
					k=0;
				i++;
			}
			else 
				i++;
		}
		if (k == 1)
		{
			ft_putstr_fd("minishell: syntax error \n", 2);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}
