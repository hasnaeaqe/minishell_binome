/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:22:40 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/04 20:45:32 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[i])
		return ;
	while (tab[i])
		free (tab[i++]);
	free (tab);
}

char	*check_in_paths(char **dirs, char *cmd)
{
	char	*tmp;
	char	*full_path;
	int		i;
	
	if (!cmd)
		return (NULL);
	i = 0;
	while (dirs && dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_tab(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}
int	is_directory(char *path)
{
	struct stat st;
	
	if (!path)
		return (0);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}


void errors(char *cmd, int mode)
{
	if (!cmd)
		return ;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (mode == 13)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		return;
	}
	if (mode == 2)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		return;
	}
	if (mode == 20)
	{
		ft_putstr_fd(": Not a directory\n", 2);
		return;
	}
	if (mode == 21)
	{
		ft_putstr_fd(": is a directory\n", 2);
		return;
	}
	ft_putstr_fd(": command not found\n", 2);
}
int check_slash_final(char *cmd)
{
	int len;
	if (!cmd)
		return (0);
	len= ft_strlen (cmd);
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
int check_cmd_path_errors(char *cmd)
{
	char *cleaned;
	
	if (!cmd)
		return (0);
	if (ft_strrchr(cmd, '/') ) //cmd[ft_strlen(cmd) - 1] == '/')
	{ 
		cleaned = ft_substr(cmd, 0, ft_strlen(cmd) - 1);
		if (access(cleaned, F_OK) == 0 && !is_directory(cleaned))
			return (errors(cmd, 20), free(cleaned), 1);
		free(cleaned);
	}
	if (access(cmd, F_OK) != 0)
		return (errors(cmd, 2), 1);
	if (is_directory(cmd))
		return (errors(cmd, 21), 1);
	if (access(cmd, X_OK) != 0)
		return (errors(cmd, 13), 1);
	return (0);
}

char	*find_cmd_path(char *cmd, t_env *env)
{
	char	*paths;
	char	**dirs;
	
	if (!cmd)
		return (NULL);	
	if (ft_strchr(cmd, '/'))
	{
		check_cmd_path_errors(cmd);
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
