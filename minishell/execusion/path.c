/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:22:40 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/26 16:05:46 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_tab(char **tab)
{
	int i;

	i = 0;
	if(!tab[i])
		return ;
	while(tab[i])
		free(tab[i++]);
	free(tab);
}
char *find_cmd_path(char *cmd, t_env *env)
{
	(void) env;
	char *tmp;
	char *full_path;
	int i;

	char *paths =get_value(env, "PATH");
	char **dirs = ft_split(paths, ':');
	if(!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_tab(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	full_path = ft_strjoin("./", cmd);
	if (access(full_path, X_OK) == 0)
	{
		ft_free_tab(dirs);
		return (full_path);
	}
	ft_free_tab(dirs);
	return NULL;
}
