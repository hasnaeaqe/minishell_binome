/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:15:23 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/02 16:51:09 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_value(t_env *env, char *key)
{
	t_env *head;
	head = env;
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

void erreur(char *dir)
{
    ft_putstr_fd("minishell: cd: ", 2);
    ft_putstr_fd(dir, 2);
    ft_putstr_fd(": ", 2);
    if (access(dir, F_OK) == 0  && access(dir, X_OK) != 0)
		ft_putstr_fd("Permission denied\n", 2);
	else if (access(dir, F_OK) != 0)
		ft_putstr_fd("No such file or directory\n", 2);
}
