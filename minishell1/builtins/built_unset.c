/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:35 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/16 16:13:53 by cbayousf         ###   ########.fr       */
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
	if (!tmp)
		return ;
	if (tmp->value)
		free(tmp->value);
	// free(tmp->key);
	tmp->key = NULL;
	tmp->value = NULL;
	free(tmp);
}

void	unset_one(t_env **head, char *key_to_unset)
{
	t_env	*tmp;
	t_env	*prev;

	if (!head || !*head || !key_to_unset)
		return ;
	tmp = *head;
	prev = NULL;
	if (tmp && tmp->key && ft_strcmp(tmp->key, key_to_unset) == 0)
	{
		*head = tmp->next;
		free_node(tmp);
		return ;
	}
	while (tmp && tmp->key && ft_strcmp(tmp->key, key_to_unset) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	tmp->next = NULL;
	free_node(tmp);
}

static void	not_valid(char *key_to_unset)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd(key_to_unset, 2);
	ft_putstr_fd(" : not a valid identifier\n", 2);
}

int	ft_unset(t_env **head, char **key_to_unset)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!head || !*head)
		return (0);
	while (key_to_unset && key_to_unset[i])
	{
		// if (!ft_strcmp(key_to_unset[i], "_"))
		// {
		// 	i++;
		// 	continue ;
		// }
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
