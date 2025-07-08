/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:22:59 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/08 12:15:21 by cbayousf         ###   ########.fr       */
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

static int	pipe_error(t_token *prev, t_token	*tmp)
{
	if (!prev || prev->type == TOK_PIPE || is_redi_operator(prev->type))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		exit_status(258, 0);
		return (1);
	}
	if (!tmp->next || tmp->next->type == TOK_PIPE
		|| is_redi_operator(tmp->next->type))
	{
		if (!tmp->next)
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		else if (is_redi_operator(tmp->next->type) && pip_redir_error(tmp))
			return (1);
		else
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		exit_status(258, 0);
		return (1);
	}
	return (0);
}

static int	word_error(t_token *tmp)
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

int	check_syntax_errors(t_token *token)
{
	t_token	*prev;
	t_token	*tmp;

	prev = NULL;
	tmp = token;
	while (tmp)
	{
		if (is_redi_operator(tmp->type) && redir_error(tmp))
			return (1);
		if (tmp->type == TOK_PIPE && pipe_error(prev, tmp))
			return (1);
		if (word_error(tmp))
			return (1);
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}
