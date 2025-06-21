/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:34 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/21 16:38:33 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	built_pwd(t_env *env, int write)
{
	char *pwd;
	t_env *tmp;

	if (!env)
		return (1);
	pwd = getcwd(NULL, 0);
	if (!pwd) // can failed ()
		pwd = get_value(env, "PWD");
	tmp = env; 
	// puts("here)))");
	while(tmp)
	{
		if (strcmp(tmp->key, "PWD") == 0)
		{
			// free(tmp->value);
			// tmp->value = NULL;
			tmp->value = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	if (write == 1)
		printf("%s\n", pwd);
	free(pwd);
	return (0);
} //le prblm not here ,the value not updated in the env

// void update_value(t_env *env)
// {
// 	t_env *tmp;
// 	tmp = env;
// 	while(tmp)
// 	{
// 		if (ft_strcmp(tmp->key, "PWD") == 0)
// 		{
			
// 		}
// 	}
// }
