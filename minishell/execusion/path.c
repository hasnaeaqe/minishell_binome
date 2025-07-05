/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:22:40 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/04 15:18:21 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab[i])
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

	i = 0;
	while (dirs[i])
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

char	*find_cmd_path(char *cmd, t_env *env)
{
	char	*paths;
	char	**dirs;
	char	*full_path;

	// if (!cmd)
	// 	return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_value(env, "PATH");
	if (!paths)
		return (NULL);
	dirs = ft_split(paths, ':');
	if (!dirs)
		return (NULL);
	full_path = check_in_paths(dirs, cmd);
	if (full_path)
		return (full_path);
	full_path = ft_strjoin("./", cmd);
	if (!full_path)
		return (ft_free_tab(dirs), NULL);
	if (access(full_path, X_OK) == 0)
		return (ft_free_tab(dirs), full_path);
	return (free(full_path), ft_free_tab(dirs), NULL);
}
