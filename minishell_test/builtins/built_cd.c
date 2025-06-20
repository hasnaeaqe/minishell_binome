/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:41:22 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/20 11:58:07 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

char *get_value(t_env *env, char *key)
{
	t_env *head = env;
	while(head && head->next)
	{
		// printf("%s\n", head->key);
		if(ft_strcmp(head->key, key) == 0)
		{
			return (head->value);
		}
		head = head->next;
	}
	return (NULL);
}
void update_value(t_env *env, char *key, char *value)
{
	t_env *new;

	while(env)
	{
		if(ft_strcmp(env->key, key))
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new = create_node(key, value);
	if(!new)
		return ;
	new->next = env;
	env = new;;
}
int	ft_cd(char **argv, t_env *env)
{
	int		r;
	char	*path;// const ? because we could change the original value without intending to
	char buf[1024];
	if (argv[1] == NULL)
	{
		path = get_value(env, "HOME");
		if(!path)
		{
			perror("path");
			return (1);
		}
	}
	else if (argv[1] && ft_strcmp(argv[1], "..") == 0)
	{
		path = argv[1];
		r = chdir(path);
		if (r == -1)
		{
			perror("operation echoue!");
		}
	}
	else if (argv[1] && ft_strcmp(argv[1], ".") == 0)
	{
		path = getcwd(buf, sizeof(buf));
		if(!path)
		{
			perror("path");
			return (1);
		}
		update_value(env, "OLDPWD", path);
		printf("oldpwd:%s\n",get_value(env, "OLDPWD"));
		return (0);
	}
	path = argv[1];
	r = chdir(path);
	if (r == -1)
	{
		ft_putstr_fd("minishell: cd: ",2);
		ft_putstr_fd(path,2);
		ft_putstr_fd(": No such file or directory\n",2);
	}
	return (0);
}

// int	main(int argc, char**argv ,char **envp)
// {
// 	t_env *env = ft_env(envp);
// 	// ft_printenv(env);
// 	// printf("----%s\n", get_value(env, "HOME"));

// 	// while(1)
// 	// {
// 		ft_cd(argv, env);
// 		printf("cwd %s\n",getcwd(NULL, 0));
// 	// }	
// }
