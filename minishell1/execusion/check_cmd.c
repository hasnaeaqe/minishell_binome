/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:48:18 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/04 20:05:52 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtins(char *cmd)
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

void reset_redir(int fd_in , int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

int check_builts(t_tree *tree,t_env **env)
{
	int fd_in = dup(STDIN_FILENO);
	int fd_out = dup (STDOUT_FILENO);
    char **cmd;
    int status = 0;

    if (!tree || !tree->argv || !tree->argv[0])
        return (1);
	if (handle_redirs(tree) != 0)
        return (1);
    cmd = tree->argv;
    if (ft_strcmp(cmd[0], "cd") == 0)
        status =  ft_cd(cmd, *env);
    if (ft_strcmp(cmd[0], "echo")== 0)
        status = ft_echo(cmd);
    else if (ft_strcmp(cmd[0], "pwd")== 0)
        status =  built_pwd(*env, 1);
	else if (ft_strcmp(cmd[0], "export") == 0)
        status =  ft_export(tree->argv, env);
    else if (ft_strcmp(cmd[0], "unset") == 0)
        status = ft_unset(env, tree->argv + 1);
    else if (ft_strcmp(cmd[0], "env")== 0)
	{
		ft_printenv(env);
        reset_redir(fd_in, fd_out);
		return (0);	
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
        built_exit(tree->argv);
    reset_redir(fd_in, fd_out);
	return (status);
}
