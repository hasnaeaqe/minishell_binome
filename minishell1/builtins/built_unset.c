/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:35 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/21 15:08:48 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid(char *str)
{
	int	i;

	if (!str)
		return (1);
	if ((!ft_isalpha(str[0]) && str[0] != '_') || ft_isdigit(str[0]))
		return (1);
	i = 1;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	free_node(t_env *tmp)
{
	if (tmp)
	{
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		tmp->key = NULL;
		tmp->value = NULL;
	}
}

void	unset_one(t_env **head, char *key_to_unset)
{
	t_env	*tmp;
	t_env	*prev;

	if (!head || !*head || !key_to_unset)
		return ;
	tmp = *head;
	prev = NULL;
	while (tmp && tmp->key)
	{
		if (ft_strcmp(tmp->key, key_to_unset) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				(*head) = tmp->next;
			free_node(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static int	not_valid(char *key_to_unset)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd(key_to_unset, 2);
	ft_putstr_fd(" : not a valid identifier\n", 2);
	return (1);
}

int	ft_unset(t_env **head, char **key_to_unset)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!head || !*head)
		return (1);
	while (key_to_unset && key_to_unset[i])
	{
		if (is_valid(key_to_unset[i]) == 0)
			unset_one(head, key_to_unset[i]);
		else
		{
			not_valid(key_to_unset[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
