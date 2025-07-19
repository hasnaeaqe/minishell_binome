/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:47:29 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/19 12:00:53 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_heredoc_files(char **filename, int *fd_write, int *fd_read)
{
	*filename = generate_filename();
	*fd_write = open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd_write == -1)
		return (perror("heredoc open write"), 1);
	*fd_read = open(*filename, O_RDONLY, 0644);
	if (*fd_read == -1)
	{
		close(*fd_write);
		return (perror("heredoc open read"), 1);
	}
	unlink(*filename);
	safe_free(filename);
	return (0);
}

static void	handle_heredoc_child(t_redir_node *redir,
		t_env *env, int fd_write, int fd_read)
{
	handle_heredoc_signals();
	close(fd_read);
	write_in_herdoc(redir, env, fd_write);
	exit(0);
}

static int	check_heredoc_status(int status, int fdread, int *stop)
{
	if (WEXITSTATUS(status) == 1 || WTERMSIG(status) == SIGINT)
	{
		*stop = 1;
		close(fdread);
		setup_signals();
		exit_status(1, 0);
		return (1);
	}
	return (0);
}

static int	process_heredoc_redir(t_redir_node *redir, t_env *env, int *stop)
{
	char	*filename;
	int		fd;
	int		fdread;
	pid_t	pid;
	int		status;

	redir->ishd = 1;
	if (open_heredoc_files(&filename, &fd, &fdread))
		return (1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		handle_heredoc_child(redir, env, fd, fdread);
	close(fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (check_heredoc_status(status, fdread, stop))
		return (1);
	redir->fd = fdread;
	redir->kind = REDIR_INPUT;
	return (0);
}

int	handle_heredoc(t_tree *tree, t_env *env, int *stop_herdoc)
{
	t_redir_node	*redir;

	if (!tree)
		return (1);
	if (tree->kind == NODE_PIPE)
	{
		handle_heredoc(tree->left, env, stop_herdoc);
		if (*stop_herdoc == 1)
			return (2);
		handle_heredoc(tree->right, env, stop_herdoc);
		return (0);
	}
	redir = tree->redirs;
	while (redir)
	{
		if (*stop_herdoc == 1)
			return (2);
		redir->ishd = 0;
		if (redir->kind == REDIR_HEREDOC)
			if (process_heredoc_redir(redir, env, stop_herdoc))
				return (2);
		redir = redir->next;
	}
	return (0);
}
