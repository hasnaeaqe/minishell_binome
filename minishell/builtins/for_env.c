/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:56:34 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/23 20:23:55 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_node(char *cle, char *val)
{
	t_env	*env;

	if (!cle)
		return (NULL);
	env = ft_malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(cle);
	env->value = ft_strdup(val);
	env->next = NULL;
	return (env);
}

int	ft_lstsize(t_env *lst)
{
	int		count;

	count = 0;
	if (!lst)
		return (count);
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

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

void	ft_printenv(t_env **head)
{
	t_env	*tmp;

	if (!head || !*head)
	{
		ft_putstr_fd("minishell: env: No such file or directory", 2);
		return ;
	}
	tmp = *head;
	while (tmp)
	{
		if (tmp->value && tmp->key)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
