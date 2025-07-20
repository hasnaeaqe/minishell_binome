/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:41:22 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/20 19:51:33 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_home(char **argv, t_env *env)
{
	char	*home;

	if (!env)
		return (1);
	if (argv && !argv[1])
	{
		home = get_value(env, "HOME");
		if (!home)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		if (chdir(home) != 0)
			return (erreur(home));
		return (0);
	}
	return (1);
}

int	point(t_env *env, char **argv)
{
	char	*pwd;

	if (!env)
		return (1);
	if (argv[1] && ft_strcmp(argv[1], ".") == 0)
	{
		pwd = get_value(env, "PWD");
		update_value(env, "OLDPWD", pwd);
		return (0);
	}
	return (1);
}

int	check_pwd(t_env *env, char *old_pwd)
{
	char	*pwd;
	char	*p;
	t_env	*tmp;

	pwd = getcwd(NULL, 0);
	p = ft_strdup(pwd);
	free(pwd);
	if (!p)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd:", 2);
		ft_putstr_fd(" cannot access parent directories: No such file or directory\n", 2);
		p = get_value(env, "PWD");
		p = ft_strjoin(p, "/..");
		if (!p)
			return (1);
		tmp = env;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, "PWD") == 0)
				update_value(env, "PWD", p);
			tmp = tmp->next;
		}
		return (update_value(env, "OLDPWD", old_pwd), 0);
	}
	update_value(env, "OLDPWD", old_pwd);
	update_value(env, "PWD", p);
	return (0);
}

int	check_double_point(char *path, char *pwd, t_env *env)
{
	char	*new_pwd;

	if (path && ft_strcmp(path, "..") == 0)
	{
		new_pwd = remove_last_slash(pwd);
		if (chdir(new_pwd) != 0)
			return (erreur(path));
	}
	else
		return (check_pwd(env, pwd), erreur(path));
	return (check_pwd(env, pwd));
}

int	ft_cd(char **argv, t_env *env)
{
	char	*path;
	char	*pwd;

	if (!env)
		return (1);
	pwd = get_value(env, "PWD");
	if (!get_home(argv, env))
		return (check_pwd(env, pwd));
	if (!point(env, argv))
		return (check_pwd(env, pwd));
	path = argv[1];
	if (chdir(path) != 0)
		return (check_double_point(path, pwd, env));
	return (check_pwd(env, pwd));
}
