/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:13:10 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/24 18:15:39 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add(t_env_copy **lst, t_env_copy *new)
{
	t_env_copy	*tmp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env_copy	*env_node(char *cle, char *val)
{
	t_env_copy	*env;

	if (!cle)
		return (NULL);
	env = ft_malloc(sizeof(t_env_copy));
	if (!env)
		return (NULL);
	env->key = ft_strdup(cle);
	env->value = ft_strdup(val);
	env->next = NULL;
	return (env);
}

t_env_copy	*create_copy_env(t_env *env)
{
	t_env_copy	*new_node;
	t_env_copy	*head;
	int			i;

	if (!env)
		return (NULL);
	head = NULL;
	i = 0;
	while (env)
	{
		new_node = env_node(env->key, env->value);
		if (!new_node)
			return (NULL);
		ft_add(&head, new_node);
		env = env->next;
	}
	return (head);
}
