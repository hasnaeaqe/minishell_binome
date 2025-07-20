/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:19:41 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/20 19:47:49 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_args(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	if ((!ft_isalpha(str[i]) && str[i] != '_') || ft_isdigit(str[i]))
		return (-1);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
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

static void	add_to_env_or_update(t_env **env, char *key_to_add,
				char *value_to_add, int mode)
{
	t_env	*new_node;
	char	*old_value;
	t_env	*existe;

	existe = find_node(*env, key_to_add);
	if (existe)
	{
		if (mode == 1)
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

static void	process_export_arg(char *arg, t_env **env)
{
	int		mode;
	char	*key;
	char	*val;
	t_env	*new_node;

	mode = parse_args(arg);
	if (mode == -1)
		return ;
	key = ext_key(arg);
	val = ext_val(arg);
	if (key && val)
		add_to_env_or_update(env, key, val, mode);
	else if (key && !val && !find_node(*env, key))
	{
		new_node = create_node(key, NULL);
		ft_lstadd_back(env, new_node);
	}
}

void	ft_add_export(char **argv, t_env **env, int *status)
{
	int	i;
	int	mode;

	i = 1;
	while (argv[i])
	{
		mode = parse_args(argv[i]);
		if (mode == -1)
		{
			ft_putstr_fd("export: not an identifier: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("\n", 2);
			*status = 1;
			i++;
			continue ;
		}
		process_export_arg(argv[i], env);
		i++;
	}
}

int	ft_export(char **argv, t_env **env)
{
	t_env	**array;
	int		size;
	int		status;

	status = 0;
	if (!env || !*env)
		return (1);
	size = ft_lstsize(*env);
	if (argv && *argv)
		ft_add_export(argv, env, &status);
	array = env_to_array(*env, size);
	if (!array || !*array)
		return (1);
	sort_list(array);
	if (argv && !argv[1])
		ft_printexport(array);
	return (status);
}
