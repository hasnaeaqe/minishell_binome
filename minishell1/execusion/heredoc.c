/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:47:29 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/17 16:19:34 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	safe_free(char **filename)
{
	while (filename && *filename)
	{
		free (*filename);
		*filename = NULL;
	}
}

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

static int	process_heredoc_redir(t_redir_node *redir, t_env *env, int *stop)
{
	char	*filename;
	int		fd;
	int		fdread;
	pid_t	pid;
	int		status;

	void (*old_hand)(int);
	redir->ishd = 1;
	if (open_heredoc_files(&filename, &fd, &fdread))
		return (1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		handle_heredoc_child(redir, env, fd, fdread);
	close(fd);
	old_hand = signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	exit_status(WEXITSTATUS(status), 0);
	signal(SIGINT, old_hand);
	printf("%d\n", WEXITSTATUS(status));
	if (WEXITSTATUS(status) == 1 && WTERMSIG(status) == SIGINT)
		return (*stop = 1, close(fdread),setup_signals(), exit_status(1, 0), 1);
	return (redir->fd = fdread, redir->kind = REDIR_INPUT, 0);
}

void	handle_heredoc(t_tree *tree, t_env *env, int *stop_herdoc)
{
	t_redir_node	*redir;

	if (!tree)
		return ;
	if (tree->kind == NODE_PIPE)
	{
		handle_heredoc(tree->left, env, stop_herdoc);
		handle_heredoc(tree->right, env, stop_herdoc);
		return ;
	}
	redir = tree->redirs;
	while (redir)
	{
		if (*stop_herdoc == 1)
			return ;
		redir->ishd = 0;
		if (redir->kind == REDIR_HEREDOC)
			if (process_heredoc_redir(redir, env, stop_herdoc))
				break ;
		redir = redir->next;
	}
}
