/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:35 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/20 18:24:25 by haqajjef         ###   ########.fr       */
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
		// if (ft_strcmp(key_to_unset[i], "_") != 0)
		// {
			if (is_valid(key_to_unset[i]) == 0)
				unset_one(head, key_to_unset[i]);
			else
			{
				not_valid(key_to_unset[i]);
				status = 1;
			}			
		// }
		i++;
	}
	return (status);
}


// void    ft_remove(t_env **head, char *key)
// {
//     t_env    *curr;
//     t_env    *prev;

//     if (!head || !*head)
//         return ;
//     curr = *head;
//     prev = NULL;
//     while (curr)
//     {
//         if (ft_strcmp(key, curr->key) == 0)
//         {
//             if (prev)
//                 prev->next = curr->next;
//             else
//                 *head = curr->next;
//             free(curr->key);
//             curr->key = NULL;
//             free(curr->value);
//             curr->value = NULL;
//             return ;
//         }
//         prev = curr;
//         curr = curr->next;
//     }
// }

// int    ft_unset(t_env **env, char **arg)
// {
//     int    i;

//     i = 0;
//     if (!env || !*env)
//         return (exit_status(1, 0));
//     while (arg && arg[++i])
//     {
//         if (is_valid(arg[i]))
//             return (not_valid(arg[i]));
//         if (ft_strcmp(arg[i], "_") != 0)
//             ft_remove(env, arg[i]);
//     }
//     return (exit_status(0, 0));
// }
