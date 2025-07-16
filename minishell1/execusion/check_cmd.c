/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:48:18 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/16 16:05:19 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static void	reset_redir(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

static int	ft_built(t_tree *tree, t_env **env, t_exec *exec, int is_child)
{
	int		status;
	char	**cmd;

	status = 0;
	cmd = tree->argv;
	if (ft_strcmp(cmd[0], "cd") == 0)
		status = ft_cd(cmd, *env);
	if (ft_strcmp(cmd[0], "echo") == 0)
		status = ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		status = built_pwd(*env, 1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		status = ft_export(tree->argv, env);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		status = ft_unset(env, tree->argv + 1);
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_printenv(env);
		reset_redir(exec->fd_in, exec->fd_out);
		return (0);
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
		status = built_exit(tree->argv, is_child);
	return (status);
}

int	check_builts(t_tree *tree, t_env *env, int is_child)
{
	t_exec	exec;
	int		status;

	exec.fd_in = dup(STDIN_FILENO);
	exec.fd_out = dup(STDOUT_FILENO);
	status = 0;
	if (!tree || !tree->argv || !tree->argv[0])
		return (1);
	if (handle_redirs(tree) != 0)
		return (1);
	status = ft_built(tree, &env, &exec, is_child);
	reset_redir(exec.fd_in, exec.fd_out);
	return (status);
}
