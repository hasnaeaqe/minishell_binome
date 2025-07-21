/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:22:59 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/21 15:10:33 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redir_error(t_token *tmp)
{
	if (!tmp->next || tmp->next->type != TOK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (tmp->next)
			ft_putstr_fd(tmp->next->value, 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
		exit_status(258, 0);
		return (1);
	}
	return (0);
}

static int	pip_redir_error(t_token	*tmp)
{
	if (!tmp->next->next || tmp->next->next->type != TOK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (tmp->next->next)
			ft_putstr_fd(tmp->next->next->value, 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
		exit_status(258, 0);
		return (1);
	}
	return (0);
}

static int	pipe_error_next_check(t_token *tmp)
{
	if (!tmp->next)
	{
		ft_putstr_fd(
			"minishell: syntax error near unexpected token `|'\n", 2);
		exit_status(258, 0);
		return (1);
	}
	else if (is_redi_operator(tmp->next->type))
	{
		if (pip_redir_error(tmp))
			return (1);
	}
	else
	{
		ft_putstr_fd(
			"minishell: syntax error near unexpected token `|'\n", 2);
		exit_status(258, 0);
		return (1);
	}
	return (0);
}

static int	pipe_error(t_token *prev, t_token *tmp)
{
	if (!prev || prev->type == TOK_PIPE
		|| is_redi_operator(prev->type))
	{
		ft_putstr_fd(
			"minishell: syntax error near unexpected token `|'\n", 2);
		exit_status(258, 0);
		return (1);
	}
	if (!tmp->next || tmp->next->type == TOK_PIPE
		|| is_redi_operator(tmp->next->type))
	{
		if (pipe_error_next_check(tmp))
			return (1);
	}
	return (0);
}

int	check_syntax_errors(t_token *token)
{
	t_token	*prev;
	t_token	*tmp;

	(1) && (prev = NULL, tmp = token);
	if (!token)
		return (1);
	while (tmp)
	{
		if (is_redi_operator(tmp->type))
		{
			if (redir_error(tmp))
				return (1);
		}
		if (tmp->type == TOK_PIPE)
		{
			if (pipe_error(prev, tmp))
				return (1);
		}
		if (word_error(tmp))
			return (1);
		prev = tmp;
		tmp = tmp->next;
	}
	max_herdoc(token);
	return (0);
}
