/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:19:41 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/26 16:49:08 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int parse_args(char *str)
{
	int i;
	i = 0;
	if (!str)
		return (-1);
	if((!ft_isalpha(str[i]) && str[i] != '_') || ft_isdigit(str[i]))
			return (-1);
	while(str[i] && str[i] != '=' && str[i] != '+')
	{
		if(!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
			return (-1);
		i++;
		
	}
	if (str[i] == '+' && str[i + 1] == '=')
		return (1);
	return (0);
}

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

// void add(int mode, t_env *existe, char *value_to_add)
// {
// 	char *old_value;
// 	if(existe)
// 	{
// 			if (mode == 0)
// 			{
// 				free(existe->value);
// 				existe->value = ft_strdup(value_to_add);
// 			}
// 			else if(mode == 1)
// 			{
// 				old_value = existe->value;
// 				existe->value = ft_strjoin(old_value, value_to_add);
// 				free(old_value);
// 			}
// 		return ;
// 	}
// }
void add_to_env_or_update(t_env **env, char *key_to_add, char *value_to_add, int mode)
{
	t_env *tmp;
	t_env *new_node;
	char *old_value;
	t_env *existe;

	tmp = *env;
	existe = find_node(*env, key_to_add);
	if(existe)
	{
			if (mode == 0)
			{
				free(existe->value);
				existe->value = ft_strdup(value_to_add);
			}
			else if(mode == 1)
			{
				old_value = existe->value;
				existe->value = ft_strjoin(old_value, value_to_add);
				free(old_value);
			}
		return ;
	}
	// add(mode,existe, value_to_add);
	new_node = create_node(key_to_add, value_to_add);
	if(!tmp)
	{
		*env = new_node;
		return;
	}
	while(tmp -> next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void ft_add_export(char **argv, t_env **env)
{
	int i;
	int mode;
	char *key;
	char *val;

	i = 1;
	while(argv[i])
	{
		mode = parse_args(argv[i]);
		if(mode == -1)
		{
			printf("export: not an identifier: %s\n", argv[i]);
			// exit(1);
			// return ;
		}
		key = ext_key(argv[i]);
		val = ext_val(argv[i]);
		if(key && val)
			add_to_env_or_update(env, key, val, mode);
		// if val null et key not in env ajouter le 
		if (!val && !find_node(*env, key))
		{
			t_env *new_node = create_node(key, NULL);
			t_env *tmp = *env;
			if(!tmp)
			{
				*env = new_node;
				return;
			}
			while(tmp -> next)
				tmp = tmp->next;
			tmp->next = new_node;
		}
		i++;
	}
}

void	ft_printexport(t_env *head)
{
	t_env	*tmp;

	tmp = head;
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

t_env **env_to_array(t_env *env, int size)
{
	t_env **array;
	t_env *tmp;
	int i;

	array = ft_malloc(sizeof(t_env *) * (size + 1));
	tmp = env;
	i= 0;
	while(i < size && tmp)
	{
		array[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
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

void ft_export(char **argv, t_env *env)
{
	t_env **array;
	int size;

	size = ft_lstsize(env);
	array = env_to_array(env, size);
	sort_list(array);
	if(argv && !argv[1])
		ft_printexport(*array);
	ft_add_export(argv, &env);
	array = env_to_array(env, size);
	sort_list(array);
}













































	