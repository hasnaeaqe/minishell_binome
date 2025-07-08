/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:35 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/08 16:35:53 by haqajjef         ###   ########.fr       */
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
	puts("ana hona");
	printf("key ----> %s\n", tmp->key);
	printf("value ----> %s\n", tmp->value);
	// if (tmp->key)
	// 	free(tmp->key);
	puts("1");
	if (tmp->value)
		free(tmp->value);
	// printf("key ----> %s\n", tmp->key);
	// printf("value ----> %s\n", tmp->value);
	puts("2");
	// tmp->key = NULL;
	// tmp->value = NULL;
	free(tmp);
	puts("3");
}

void	unset_one(t_env **head, char *key_to_unset)
{
	t_env	*tmp;
	t_env	*prev;

	if (!head || !*head)
		return ;
	tmp = *head;
	prev = NULL;
	if (tmp && ft_strcmp(tmp->key, key_to_unset) == 0)
	{
		*head = tmp->next;
		free_node(tmp);
		return ;
	}
	while (tmp && ft_strcmp(tmp->key, key_to_unset) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	printf("{{{---> }}}%s\n", prev->key);
	printf("{{{---> }}}%s\n", prev->value);
	printf("---> %s\n", tmp->key);
	printf("---> %s\n", tmp->value);
	puts("here");
	if (!tmp)
		return ;
	prev->next = tmp->next;
	tmp->next = NULL;
	puts("0");
	free_node(tmp);
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
		if (is_valid(key_to_unset[i]) == 0)
			unset_one(head, key_to_unset[i]);
		else
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(key_to_unset[i], 2);
			ft_putstr_fd(" : not a valid identifier\n", 2);
			status = 1;
		}
		i++;
	}
	return (status);
}
