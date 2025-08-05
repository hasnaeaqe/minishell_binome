/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:50:04 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/26 12:01:56 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static pid_t	create_child(int pipefd[2], t_tree *child_tree,
							t_env *env, int is_left)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), exit(EXIT_FAILURE), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (is_left)
			dup2(pipefd[1], STDOUT_FILENO);
		else
			dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(exec_tree(child_tree, &env, 1));
	}
	return (pid);
}

int	execute_pipe(t_tree *tree, t_env *env)
{
	int		pipefd[2];
	pid_t	pid_right;
	int		status;

	if (!tree)
		return (1);
	status = 0;
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	create_child(pipefd, tree->left, env, 1);
	pid_right = create_child(pipefd, tree->right, env, 0);
	signal(SIGINT, SIG_IGN);
	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(pid_right, &status, 0);
	while (wait(NULL) != -1)
		;
	setup_signals();
	return (status_exit(status));
}
