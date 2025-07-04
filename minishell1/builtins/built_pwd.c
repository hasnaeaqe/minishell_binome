/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:34 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/04 15:47:40 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_pwd(t_env *env, int write)
{
	char *pwd;
	t_env *tmp;

	if (!env)
		return (1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = get_value(env, "PWD");
	tmp = env; 
	while(tmp)
	{
		update_value(env, "PWD", pwd);
		tmp = tmp->next;
	}
	if (write == 1)
		printf("%s\n", pwd);
	free(pwd);
	return (0);
} //le prblm not here ,the value not updated in the env