/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:19:41 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/12 21:46:30 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

int parse_args(char *str)
{
	int i;
	i = 0;
	while(str[i] && str[i] != '=' && str[i] != '+')
	{
		if((!ft_isalpha(str[i]) && str[i] != '_') || ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	if (str[i] == '+' && str[i + 1] == '=')
		return (1);
	return (0);
}

// int is_key_in_env(t_env *env, char *key_to_search)
// {
// 	t_env *tmp;
// 	tmp = env;
// 	while(tmp)
// 	{
// 		if(ft_strcmp(tmp->key, key_to_search) == 0)
// 			return (1);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
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
	new_node = create_node(key_to_add, value_to_add);
	if(!tmp)
	{
		*env = new_node;
		return;
	}
	while(tmp -> next)
	{
		tmp = tmp->next;
	}
	tmp->next = new_node;
}

// void add_to_env(t_env **env, char *key_to_add, char *value_to_add)
// {
// 	t_env *tmp;
// 	t_env *new_node;

// 	new_node = create_node(key_to_add, value_to_add);
// 	tmp = *env;
// 	if(!tmp)
// 	{
// 		*env = new_node;
// 		return;
// 	}
// 	while(tmp -> next)
// 	{
// 		tmp = tmp->next;
// 	}
// 	tmp->next = new_node;
// }


void ft_add_export(char **argv, t_env **env)
{
	int i;
	int mode;

	i = 1;
	while(argv[i])
	{
		mode = parse_args(argv[i]);
		if(mode == -1)
		{
			printf("export: not an identifier:%s\n", argv[i]);
			exit(1);
		}
		char *key = ext_key(argv[i]);
		char *val = ext_val(argv[i]);
		if(key != NULL)
			add_to_env_or_update(env, key, val, mode);
		else
			add_to_env_or_update(env, argv[i], "", mode);
		i++;
	}
}


// void    ft_lstadd_back(t_env **lst, t_env *new)
// {
// 	t_env    *tmp;

// 	if (lst == NULL || new == NULL)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		new->next = NULL;
// 		return ;
// 	}
// 	else
// 	{
// 		tmp = *lst;
// 		while (tmp -> next)
// 		{
// 			tmp = tmp-> next;
// 		}
// 		tmp -> next = new;
// 	}
// }

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
	while(i< size && tmp)
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

void ft_export(int argc, char **argv, char **env)
{
	t_env **array;
	t_env *list;
	int size;

	list = ft_env(env);
	size = ft_lstsize(list);
	array = env_to_array(list, size);
	sort_list(array);
	if(argc == 1)
	{
		ft_printexport(*array);
	}
	ft_add_export(argv, &list);
	array = env_to_array(list, size);
	sort_list(array);
	ft_printexport(*array);
}
// int main(int argc, char **argv, char **env)
// {
// 	// t_env *list;
	// list = ft_env(env);
	// t_env **array = env_to_array(list, ft_lstsize(list));
	// sort_list(array);
	// if(argc == 1)
	// {
	// 	ft_printexport(*array);
	// }
	// // t_env *head =  NULL;
	// // int i = 1;
	// // while(argv[i])
	// // {
	// // 	if(check_key(argv[i]) == 1)
	// // 	{
	// // 		char *key = ext_key(argv[i]);
	// // 		char *val = ext_val(argv[i]);
	// // 		t_env *new = create_node(key, val);
	// // 		ft_lstadd_back(&head, new);
	// // 	}
	// // 	else
	// // 	{
	// // 		t_env *nov = create_node(argv[i], NULL);
	// // 		ft_lstadd_back(&head, nov);
	// // 	}
	// // 	i++;
	// // }
	// // ft_printenv(head);

	// // printf("\nAprès export :\n");
	// ft_add_export(argv, array);
	// sort_list(array);
	// printf("---------export------------\n");
	// ft_printexport(*array);
// 	ft_export(argc, argv, env);
// 	return 0;
// }

// int main(int argc, char **argv, char **env)
// {
// 	ft_export(argc, argv, env);
// 	return 0;
// }
