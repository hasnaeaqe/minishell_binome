/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:29 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/29 12:03:46 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *find_node(t_env *env, char *key)
{
    t_env *tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

int	ft_lstsize(t_env *lst)
{
	int		count;
	t_env	*head;

	count = 0;
	head = lst;
	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
} 

void	ft_printexport(t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if(tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else if(tmp->key){
			printf("declare -x %s\n", tmp->key);
		}
		tmp = tmp->next;
	}
}
void swap_nodes(t_env *a, t_env *b)
{
	char *tmpa;
	char *tmpb;

	tmpa = a->key;
	a->key = b->key;
	b->key = tmpa;

	tmpb = a->value;
	a->value = b->value;
	b->value = tmpb;

}

void sort_list(t_env **env)
{
	t_env *tmp;
	int swapped;

	swapped = 1;
	if(!env || !(*env) || (*env)->next == NULL)
		return ;
	while(swapped)
	{
		swapped = 0;
		tmp = *env;
		while(tmp && tmp->next)
		{
			if(ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				swap_nodes(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
	}
}
