/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:19:58 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/20 12:26:07 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../parsing/minishell.h"

t_env	*create_node(char *cle, char *val)
{
	t_env	*env;

	if (!cle || !val)
		return(NULL);
	env = ft_malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = cle;
	env->value = val;
	env->next = NULL;
	return (env);
}

char *ext_key(char *str)
{
    int i = 0;
	if(!str)
		return(NULL);
    while (str[i] && str[i] != '=' && str[i] != '+')
        i++;
    char *key = ft_malloc(sizeof(char) *(i + 1));
    ft_strncpy(key, str, i);
	key[i] = '\0';
    return key;
}

char	*ext_val(char *env)
{
	char *equal;
	char *val;

	equal = ft_strchr(env, '=');
	if(!equal)
		return(NULL);
	val = ft_strdup(equal + 1);
	return (val);
}

void	ft_printenv(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if(tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

t_env *ft_env(char **env)
{
	t_env	*ev;
	t_env	*new_node;
	t_env	*head;
	int		i;

	if (env && !*env)
		return (env_vide());
	ev = NULL;
	head = NULL;
	i = 0;
	new_node = create_node(ext_key(env[i]), ext_val(env[i]));
	head = new_node;
	ev = head;
	while (env[i])
	{
		new_node = create_node(ext_key(env[i]), ext_val(env[i]));
		if (!new_node)
			return (ev);
		ev->next = new_node;
		ev = new_node;
		i++;
	}
	return (head);
}
//empty env
void    ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env    *tmp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	else
	{
		tmp = *lst;
		while (tmp -> next)
		{
			tmp = tmp-> next;
		}
		tmp -> next = new;
	}
}

t_env *env_vide()
{
	char *pwd;
	char *path;
	pwd=getcwd(NULL, 0);
	t_env *env;
	env = NULL;
	path = "PATH=/mnt/homes/haqajjef/.docker/bin:/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	ft_lstadd_back(&env, create_node(ext_key(path), ext_val(path)));
	ft_lstadd_back(&env, create_node(ext_key(pwd), ext_val(pwd)));
	ft_lstadd_back(&env, create_node(ext_key("SHLVL=1"), ext_val("SHLVL=1")));
	ft_lstadd_back(&env, create_node(ext_key("_=/usr/bin/env"), ext_val(("_=/usr/bin/env"))));
	return (env);
}
// char *get_value(t_env *env, char *key)
// {
// 	while(env)
// 	{
// 		if(ft_strcmp(env->key, key))
// 			return (env->value);
// 		env = env->next;
// 	}
// 	return (NULL);
// }

// int	main(int argc, char **argv, char **env)
// {
// 	t_env	*head;

// 	(void)argc;
// 	(void)argv;
// 	head = ft_env(env);
// 	ft_printenv(head);
// 	return (0);
// }
