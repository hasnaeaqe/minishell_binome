/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:41:22 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/22 18:07:51 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

char *get_value(t_env *env, char *key)
{
	t_env *head = env;
	while(head)
	{
		if(ft_strcmp(head->key, key) == 0)
		{
			return (head->value);
		}
		head = head->next;
	}
	return (NULL);
}
void update_value(t_env *env, char *key, char *value)
{
	t_env *new;
	t_env *tmp = env;

	while(tmp)
	{
		if(ft_strcmp(tmp->key, key) == 0)
		{
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = create_node(key, value);
	if(!new)
		return ;
	while (env && env->next)
		env = env->next;
	env->next = new;
}

void update_old_pwd(t_env *env, char *old)
{
	t_env *tmp;
	tmp = env;
	while(tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			update_value(env,"OLDPWD" ,old);
			return ;
		}
		tmp = tmp->next;	 
	}
}

void ft_write_error(char *str)
{
	write(2, str, ft_strlen(str));
}
char *remove_last_slash(char *path)
{
	size_t len;
	char *rest;

	len = ft_strlen(path);
	len --;
	int i = len;
	while (i > 0 && path[i] == '\'')
		i --;
	while (i > 0 && path[i] != '\'')
		i --;
	rest = ft_strndup(path, len);
	return (rest);
}
void put_errno(char *dir)
{
	if (errno == 13)
	{
		ft_write_error("minishell: cd: ");
		ft_write_error(dir);
		ft_write_error(": Permission denied\n");
	}
	else if (errno == 2)
	{
		ft_write_error("minishell: cd: ");
		ft_write_error(dir);
		ft_write_error(": No such file or directory\n");
	}
}

int get_home(char **argv, t_env *env)
{
	char *home;
	if (!env)
		return (1);
	if (argv && !argv[1])
	{
		home = get_value(env, "HOME");
		if(!home)
			return(ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		if (chdir(home) != 0)
		{
			ft_putstr_fd("minishell: cd: ",2);
			ft_putstr_fd(home,2);
			ft_putstr_fd(": No such file or directory\n",2);
			return (127);
		}
		return (0);
	}
	return (1);
}
int point(t_env *env, char **argv)
{
	char *pwd;

	if (!env)
		return (1);
	if (argv[1] && ft_strcmp(argv[1], ".") == 0)
	{
		pwd = get_value(env, "PWD");
		update_value(env, "OLDPWD", pwd);
		return (0);
	}
	// free(pwd); //segfault
	return (1);
}

int check_pwd(t_env *env, char *old_pwd)
{
	char *pwd;
	t_env *tmp;

	if (!env)
		return (1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		pwd = get_value(env, "PWD");
		pwd = ft_strjoin(pwd, "/..");
		if (!pwd)
			return (1);
		tmp = env;
		while(tmp)
		{
			if (ft_strcmp(tmp->key, "PWD") == 0)
				update_value(env,"PWD" ,pwd);
			tmp = tmp->next;
		}
		update_old_pwd(env, old_pwd);
		return (1);
	}
	update_old_pwd(env, old_pwd);
	return (0);
}
int check_double_point(char *path, char *pwd)
{
	char *new_pwd;

	if (ft_strcmp(path, "..") == 0)
		{
			new_pwd = remove_last_slash(pwd);
			if(chdir(new_pwd) != 0)
				return (put_errno(path), 1);
		}	
	else
	{
		put_errno(path);
		return (1);
	}
}
int	ft_cd(char **argv, t_env *env)
{
	char	*path;       // const ? because we could change the original value without intending to 
	char *pwd;

	pwd = get_value(env, "PWD");
	if(!get_home(argv, env))
		return (check_pwd(env, pwd));

	if(!point(env, argv))
		return (check_pwd(env, pwd));

	path = argv[1];
	if (chdir(path) != 0)
	{
		// if (ft_strcmp(path, "..") == 0)
		// {
		// 	char *new_pwd = remove_last_slash(pwd);
		// 	if(chdir(new_pwd) != 0)
		// 		return (put_errno(path), 1);
		// }	
		// else
		// {
		// 	put_errno(path);
		// 	return (1);
		// }
		check_double_point(path, pwd);
	} 
	else
	{
		update_value(env, "PWD", path);
		return (check_pwd(env, pwd));
	}
	return (check_pwd(env, pwd));
}
