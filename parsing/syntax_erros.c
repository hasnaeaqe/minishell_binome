/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_erros.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:22:59 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/11 11:36:20 by haqajjef         ###   ########.fr       */
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
					ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				else
					ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				return (1);
			}
		}
		if (ft_stchr(tmp->value, '\'') % 2 != 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `''\n", 2);
			return (1);
		}
		if (ft_stchr(tmp->value,'"') % 2 != 0)
		{ 
			ft_putstr_fd("minishell: syntax error near unexpected token `\"'\n", 2);
			return (1);
		}
		if (ft_strcmp(tmp->value, "!") == 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			return (1);
		}
		if (ft_strncmp(tmp->value, ";", 1) == 0)
		{
			if (ft_strncmp(tmp->value, ";;", 2) == 0)
				ft_putstr_fd("minishell: syntax error near unexpected token `;;'\n", 2);
			else
				ft_putstr_fd("minishell: syntax error near unexpected token `;'\n", 2);
			return (1);
		}
		if (ft_strncmp(tmp->value, "&", 1) == 0)
		{
			if (ft_strncmp(tmp->value, "&&", 2) == 0)
				ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
			else
				ft_putstr_fd("minishell: syntax error near unexpected token `&'\n", 2);
			return (1);
		}
		if (ft_strncmp(tmp->value, "(", 1) == 0
			|| ft_strncmp(tmp->value, ")", 1) == 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `)'\n", 2);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}
