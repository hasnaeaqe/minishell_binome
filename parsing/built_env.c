/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:19:58 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/13 15:53:31 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_env	*create_node(char *cle, char *val)
{
	t_env	*env;

	env = ft_malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = cle;
	env->value = val;
	env->next = NULL;
	return (env);
}

char *ext_key(char *str) {
    int i = 0;
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

	equal = ft_strchr1(env, '=');
	if(!equal)
		return(NULL);
	val = ft_strdup1(equal + 1);
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

	ev = NULL;
	head = NULL;
	i = 0;
	new_node = create_node(ext_key(env[i]), ext_val(env[i]));
	head = new_node;
	ev = head;
	while (env[i])
	{
		new_node = create_node(ext_key(env[i]), ext_val(env[i]));
		ev->next = new_node;
		ev = new_node;
		i++;
	}
	return (head);
}
// int	main(int argc, char **argv, char **env)
// {
// 	t_env	*head;
// 	int i = 0;
// 	(void)argc;
// 	(void)argv;
// 	head = ft_env(env);
// 	ft_printenv(head);
// 	return (0);
// }
