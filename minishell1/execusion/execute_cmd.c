/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:17:10 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/04 12:09:31 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute_cmd(t_tree *tree, t_env **env) {
	
	pid_t pid;
	int status;
	char **array;

	if (!tree)
		return (1);
	status = 0;
	array = to_array(*env, ft_lstsize(*env));
	if (tree && is_builtins(*tree->argv) == 1)
		return (check_builts(tree, env));
	char *path = find_cmd_path(tree->argv[0], *env);
	if (!path)
	{
		errors(tree->argv[0], 2);
		return (127);
	}
	else if (path && is_directory(path) && !ft_strchr(tree->argv[0], '/'))
	{
		errors(tree->argv[0], 33);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		puts("ana hona \n ");
		handle_redirs(tree);
		if (tree->argv && tree->argv[0] && execve(path, tree->argv, array) == -1)
			exit (EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &status, 0);
	free(path);
	return (WEXITSTATUS(status));
}

int execute_pipe(t_tree *tree, t_env *env)
{
	int pipefd[2];
	pid_t pid_left;
	pid_t pid_right;
	int status;

	if (!tree)
		return (1);
	status = 0;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		// exit(1);
	}
	pid_left = fork();
	if (pid_left == -1)
	{
		perror ("fork left");
		exit(1);
	}
	if (pid_left == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]); 
		close(pipefd[1]);
		exec_tree(tree->left, &env);// should return int (status )
		exit(127);
	}
	pid_right =  fork();
	if (pid_right == -1)
	{
		perror ("fork right");
		exit(1);
	}
	if(pid_right == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		close(pipefd[0]);
		exec_tree(tree->right, &env);
		exit(127);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	
	waitpid(pid_left, NULL, 0); 
	waitpid(pid_right, &status, 0);
	// (wait(NULL)); // while wait didn't return -1 call it again 
	return (WEXITSTATUS(status));
}

int exec_tree(t_tree *tree, t_env **env)
{
	if (!tree)
		return (1);
	if (tree->kind == NODE_COMMAND)
		return(execute_cmd(tree, env));
	else if (tree->kind == NODE_PIPE)
		return (execute_pipe(tree, *env));
	return (0);
}
