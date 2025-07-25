/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:29 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/24 18:12:53 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_node(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && key && ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env_copy	**env_to_array(t_env_copy *env, int size)
{
	t_env_copy	**array;
	t_env_copy	*tmp;
	int			i;

	array = ft_malloc(sizeof(t_env_copy *) * (size + 1));
	if (!array)
		return (NULL);
	tmp = env;
	i = 0;
	while (i < size && tmp)
	{
		array[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	ft_printexport(t_env_copy **head)
{
	t_env_copy	*tmp;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		if (tmp->value && ft_strcmp(tmp->key, "_") != 0)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else if (tmp->key && ft_strcmp(tmp->key, "_") != 0)
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

void	swap_nodes(t_env_copy *a, t_env_copy *b)
{
	char	*tmpa;
	char	*tmpb;

	tmpa = a->key;
	a->key = b->key;
	b->key = tmpa;
	tmpb = a->value;
	a->value = b->value;
	b->value = tmpb;
}

void	sort_list(t_env_copy **env)
{
	t_env_copy	*tmp;
	int			swapped;

	swapped = 1;
	if (!env || !(*env) || (*env)->next == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		tmp = *env;
		while (tmp && tmp->next)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				swap_nodes(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
	}
}
