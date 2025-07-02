/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:19:41 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/29 12:21:44 by haqajjef         ###   ########.fr       */
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
	if (str[i] == '+')
	{
		if (str[i + 1] != '=')
			return (-1);
		return (1);
	}
	return (0);
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
			if(mode == 1)
			{
				old_value = existe->value;
				existe->value = ft_strjoin(old_value, value_to_add);
				free(old_value);
			}
			else if (mode == 0)
			{
				free(existe->value);
				existe->value = NULL;
				existe->value = ft_strdup(value_to_add);
			}
		return ;
	}
	new_node = create_node(key_to_add, value_to_add);
	ft_lstadd_back(env, new_node);
}
void ft_add_export(char **argv, t_env **env)
{
	int i;
	int mode;
	char *key;
	char *val;
	t_env *new_node;

	i = 1;
	while(argv[i])
	{
		mode = parse_args(argv[i]);
		if(mode == -1)
		{
			printf("export: not an identifier: %s\n", argv[i]);
			if (!argv[i + 1])
				return;
			i++;
		}
		key = ext_key(argv[i]);
		val = ext_val(argv[i]);
		if(key && val)
			add_to_env_or_update(env, key, val, mode);
		if (!val && !find_node(*env, key))
		{
			new_node = create_node(key, NULL);
			ft_lstadd_back(env, new_node);
		}
		i++;
	}
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

int ft_export(char **argv, t_env **env)
{
	t_env **array;
	int size;

	size = ft_lstsize(*env);
	if (argv && *argv)
		ft_add_export(argv, env);
	array = env_to_array(*env, size);
	sort_list(array);
	if(argv && !argv[1])
		ft_printexport(array);
	return (0);
}
