/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:17:10 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/19 20:33:42 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_no_path_case(t_tree *tree, t_env **env, \
			char **array, char *path)
{
	char	*join;

	if (!get_value(*env, "PATH"))
	{
		join = ft_strjoin("./", tree->argv[0]);
		if (access(join, X_OK) == 0)
		{
			execve(join, tree->argv, array);
			free(join);
			exit(EXIT_FAILURE);
		}
		else
		{
			errors(tree->argv[0], 2);
			free(join);
		}
	}
	else
		errors(tree->argv[0], 33);
	free(path);
	exit(127);
}

static void	exec_path(t_tree *tree, t_env **env, char **array)
{
	char	*path;
	int		status;

	status = -1;
	if (handle_redirs(tree))
		exit(1);
	path = find_cmd_path(tree->argv[0], *env, &status);
	if (status != -1 && status != 0)
		exit(status);
	if (!path || (is_directory(path) && !ft_strchr(tree->argv[0], '/')))
		handle_no_path_case(tree, env, array, path);
	if (tree->argv && tree->argv[0] && execve(path, tree->argv, array) == -1)
	{
		free(path);
		exit(EXIT_FAILURE);
	}
	free(path);
	exit(EXIT_SUCCESS);
}

int	execute_cmd(t_tree *tree, t_env **env, int is_child)
{
	pid_t	pid;
	int		status;
	char	**array;

	if (!tree)
		return (1);
	status = 0;
	array = to_array(*env, ft_lstsize(*env));
	if (!array)
		return (1);
	if (tree && is_builtins(*tree->argv))
		return (check_builts(tree, *env, is_child));
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		exec_path(tree, env, array);
	}
	else
		(signal(SIGINT, SIG_IGN), waitpid(pid, &status, 0), setup_signals());
	return (status_exit(status));
}

int	exec_tree(t_tree *tree, t_env **env, int is_child)
{
	if (!tree)
		return (1);
	if (tree->kind == NODE_COMMAND)
		return (execute_cmd(tree, env, is_child));
	else if (tree->kind == NODE_PIPE)
		return (execute_pipe(tree, *env));
	return (0);
}
