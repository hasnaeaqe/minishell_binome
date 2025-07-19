/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:47:29 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/19 20:24:29 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	safe_free(char **filename)
{
	while (filename && *filename)
	{
		free (*filename);
		*filename = NULL;
	}
}

static int	handle_input(t_redir_node *redir)
{
	int	fd;

	if (redir->ambiguous)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		exit_status(1, 0);
		return (1);
	}
	if (redir->ishd == 1)
		fd = redir->fd;
	else
		fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
		return (1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), 1);
	return (close(fd), 0);
}

static int	handle_output(t_redir_node *redir)
{
	int	fd;

	if (redir->ambiguous == 1)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		exit_status(1, 0);
		return (1);
	}
	fd = open(redir->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), 1);
	return (close(fd), 0);
}

static int	handle_append(t_redir_node *redir)
{
	int	fd;

	if (redir->ambiguous)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		exit_status(1, 0);
		return (1);
	}
	fd = open(redir->filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		return (1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), 1);
	return (close(fd), 0);
}

int	handle_redirs(t_tree *tree)
{
	t_redir_node	*redir;

	redir = tree->redirs;
	while (redir)
	{
		if (redir->kind == REDIR_INPUT)
		{
			if (handle_input(redir))
				return (1);
		}
		else if (redir->kind == REDIR_OUTPUT)
		{
			if (handle_output(redir))
				return (1);
		}
		else if (redir->kind == REDIR_APPEND)
		{
			if (handle_append(redir))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}
