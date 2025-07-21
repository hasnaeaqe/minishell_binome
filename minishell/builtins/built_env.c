/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:19:58 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/21 17:04:07 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ext_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	key = ft_strndup(str, i);
	return (key);
}

char	*ext_val(char *env)
{
	char	*equal;
	char	*val;

	if (!env)
		return (NULL);
	equal = ft_strchr(env, '=');
	if (!equal)
		return (NULL);
	val = ft_strdup(equal + 1);
	return (val);
}

t_env	*ft_env(char **env)
{
	t_env	*new_node;
	t_env	*head;
	int		i;

	if (!env || !*env)
		return (env_vide());
	head = NULL;
	i = 0;
	while (env && env[i])
	{
		new_node = create_node(ext_key(env[i]), ext_val(env[i]));
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&head, new_node);
		i++;
	}
	update_value(head, "OLDPWD", NULL);
	update_value(head, "_", "/usr/bin/env");
	if (!head)
		exit(1);
	return (head);
}

t_env	*env_vide(void)
{
	char	*pwd;
	char	*path;
	t_env	*env;

	env = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	path = "PATH=/mnt/homes/haqajjef/.docker/bin:/usr/gnu/bin:"
		"/usr/local/bin:/bin:/usr/bin";
	ft_lstadd_back(&env, create_node("OLDPWD", NULL));
	ft_lstadd_back(&env, create_node(ext_key(path), ext_val(path)));
	ft_lstadd_back(&env, create_node("PWD", pwd));
	ft_lstadd_back(&env, create_node(ext_key("SHLVL=1"), ext_val("SHLVL=1")));
	ft_lstadd_back(&env, \
	create_node(ext_key("_=/usr/bin/env"), ext_val("_=/usr/bin/env")));
	return (env);
}
