/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:07:22 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/16 20:16:55 by haqajjef         ###   ########.fr       */
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
		free(tab[i++]);
	free(tab);
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
	struct stat	st;

	if (!path)
		return (0);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;
	
	if (!s1 && !s2)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	res = ft_strjoin(tmp, s3);
	// free(tmp);
	return (res);
}

char	**to_array(t_env *env, int size)
{
	char	**array;
	t_env	*tmp;
	int		i;

	array = ft_malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp && i < size)
	{
		array[i] = ft_strjoin_3(tmp->key, "=", tmp->value);
		if (!array[i])
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
