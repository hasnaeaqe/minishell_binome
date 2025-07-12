/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:22:40 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/12 20:25:59 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	errors(char *cmd, int mode)
{
	if (!cmd)
		exit(0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);\
	if (mode == 13)
		return (ft_putstr_fd(": Permission denied\n", 2), 126);
	if (mode == 2)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (mode == 20)
	{
		ft_putstr_fd(": Not a directory\n", 2);
		return (126);
	}
	if (mode == 21)
	{
		ft_putstr_fd(": is a directory\n", 2);
		return (126);
	}
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}

int	check_slash_final(char *cmd)
{
	int	len;

	if (!cmd)
		return (0);
	len = ft_strlen(cmd);
	if (cmd[len - 1] == '/')
	{
		cmd[len - 1] = '\0';
		if (access(cmd, F_OK) == 0 && !is_directory(cmd))
		{
			cmd[len - 1] = '/';
			return (1);
		}
		cmd[len - 1] = '/';
	}
	return (0);
}

int	check_cmd_path_errors(char *cmd)
{
	char	*cleaned;

	if (!cmd)
		return (0);
	if (ft_strlen(cmd) > 0 && cmd[ft_strlen(cmd) - 1] == '/')
	{
		cleaned = ft_substr(cmd, 0, ft_strlen(cmd) - 1);
		if (!cleaned)
			return (1);
		if (access(cleaned, F_OK) == 0 && !is_directory(cleaned))
		{
			free(cleaned);
			return (errors(cmd, 20));
		}
		free(cleaned);
	}
	if (access(cmd, F_OK) != 0)
		return (errors(cmd, 2));
	if (is_directory(cmd))
		return (errors(cmd, 21));
	if (access(cmd, X_OK) != 0)
		return (errors(cmd, 13));
	return (0);
}

char	*find_cmd_path(char *cmd, t_env *env, int *status)
{
	char	*paths;
	char	**dirs;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		*status = check_cmd_path_errors(cmd);
		return (ft_strdup(cmd));
	}
	paths = get_value(env, "PATH");
	if (!paths)
		return (NULL);
	dirs = ft_split(paths, ':');
	if (!dirs)
		return (NULL);
	paths = check_in_paths(dirs, cmd);
	if (paths)
		return (paths);
	paths = ft_strjoin("./", cmd);
	if (!paths)
		return (ft_free_tab(dirs), NULL);
	if (access(paths, X_OK) == 0)
		return (ft_free_tab(dirs), paths);
	return (free(paths), ft_free_tab(dirs), NULL);
}
