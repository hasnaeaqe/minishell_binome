/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:35 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/26 15:34:57 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

// oparse like export
int is_valid(char *str)
{
	int i;
	if (!str)
		return (1);
	if((!ft_isalpha(str[0]) && str[0] != '_') || ft_isdigit(str[0]))
		return (1);
	i = 1;
	while(str[i])
	{
		if(!ft_isalpha(str[i]) || str[i] != '_' || !ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	unset_one(t_env **head, char *key_to_unset)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *head;
	prev = NULL;
	if (!tmp)
		return;
	if (tmp && ft_strcmp(tmp->key, key_to_unset) == 0)
	{
		*head = tmp->next;
		free(tmp->key);
		free(tmp->value);
		//tmp->key = NULL; tmp->value = NULL;
		free(tmp);
		return ;
	}
	while (tmp && ft_strcmp(tmp->key, key_to_unset) != 0)
	{
		prev = tmp;
		tmp =tmp->next;
	}
	if(!tmp)
		return;
	prev->next = tmp->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}
void ft_unset(t_env **head, char **key_to_unset)
{
	int i = 0;
	while(key_to_unset[i])
	{
		if (is_valid(key_to_unset[i]) == 0)
			unset_one(head, key_to_unset[i]);
		else
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(key_to_unset[i], 2);
			ft_putstr_fd(" : not a valid identifier\n", 2);
			return ;
		}
		i++;
	}
}
