/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:19:58 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/08 18:24:13 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../executer.h"

static void	ft_free(void *p, int k)
{
	static void		*lst[INT_MAX];
	static size_t	i;

	if (k)
	{
		while (lst[i])
			free(lst[i--]);
	}
	else
		lst[i++] = p;
}

void	ft_exit(int n)
{
	ft_free(NULL, 1);
	exit(n);
}

void	*ft_malloc(size_t i)
{
	void	*k;

	k = malloc(i);
	if (!k)
		ft_exit(1);
	ft_free(k, 0);
	return (k);
}

t_env	*create_node(char *cle, char *val)
{
	t_env	*env;

	env = ft_malloc(sizeof(t_env));
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
	while (env[i] && env[i] != '=' && env[i] != '+')
		i++;
	if (env[i] != '=' || env[i] != '+')
		return (NULL);
	key = ft_malloc(sizeof(char) * (i + 1));
	i = 0;
	while (env[i] && env[i] != '=' && env[i] != '+')
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
	value = ft_malloc(sizeof(char) * ((ft_strlen(env) - i) + 1));
	i++;
	k = 0;
	while (env[i])
	{
		value[k] = env[i];
		k++;
		i++;
	}
	value[k] = '\0';
	return (value);
}
int check_key(char *str)
{
    int i;
    i = 0;
    while(str[i])
    {
        if(str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}
void	ft_printenv(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if(tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}


t_env *ft_env(char **env)
{
	t_env	*ev;
	t_env	*new_node;
	t_env	*head;
	int		i;

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
	return (head);
}
// int	main(int argc, char **argv, char **env)
// {
// 	t_env	*head;

// 	(void)argc;
// 	(void)argv;
// 	head = ft_env(env);
// 	ft_printenv(head);
// 	return (0);
// }
