/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:10:49 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/01 18:13:29 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

t_env	*create_node(char *cle, char *val)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = cle;
	env->value = val;
	env->next = NULL;
	return (env);
}

char	*ext_key(char *env)
{
	int		i;
	char	*key;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] != '=')
		return (NULL);
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*ext_val(char *env)
{
	int		i;
	int		k;
	char	*value;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] != '=')
		return (NULL);
	value = malloc(sizeof(char) * ((ft_strlen(env) - i) + 1));
	if (!value)
		return (NULL);
	i++;
	k = 0;
	while (env[i])
	{
		value[k] = env[i];
		k++;
		i++;
	}
	return (value);
}

void	ft_printenv(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env	*ev;
	t_env	*new_node;
	t_env	*head;
	int		i;

	(void)argc;
	(void)argv;
	ev = NULL;
	head = NULL;
	i = 0;
	new_node = create_node(ext_key(env[i]), ext_val(env[i]));
	head = new_node;
	ev = head;
	while (env[i])
	{
		new_node = create_node(ext_key(env[i]), ext_val(env[i]));
		ev->next = new_node;
		ev = new_node;
		i++;
	}
	ft_printenv(head);
	return (0);
}
