/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:15:23 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/24 18:12:19 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value(t_env *env, char *key)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

void	update_value(t_env *env, char *key, char *value) ///
{
	t_env	*new;
	t_env	*tmp;

	tmp = env;
	if (!env)
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = create_node(key, value);
	if (!new)
		return ;
	while (env && env->next)
		env = env->next;
	env->next = new;
}

char	*remove_last_slash(char *path)
{
	size_t	len;
	int		i;
	char	*rest;

	len = ft_strlen(path);
	len--;
	i = len;
	while (i > 0 && path[i] == '/')
		i--;
	while (i > 0 && path[i] != '/')
		i--;
	rest = ft_strndup(path, i + 1);
	return (rest);
}

int	erreur(char *dir)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": ", 2);
	if (access(dir, F_OK) == 0 && access(dir, X_OK) != 0)
		return (ft_putstr_fd("Permission denied\n", 2), 1);
	else if (access(dir, F_OK) != 0)
		return (ft_putstr_fd("No such file or directory\n", 2), 1);
	return (0);
}

int	get_home(char **argv, t_env *env)
{
	char	*home;

	if (!env)
		return (1);
	if (argv && !argv[1])
	{
		home = get_value(env, "HOME");
		if (!home)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 0);
		if (chdir(home) != 0)
			return (erreur(home));
		return (0);
	}
	return (1);
}
