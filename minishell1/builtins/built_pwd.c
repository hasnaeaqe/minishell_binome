/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:34 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/16 16:20:36 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_pwd(t_env *env, int write)
{
	char	*pwd;
	t_env	*tmp;

	if (!env)
		return (1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = get_value(env, "PWD");
		if (!pwd)
			return (1);
	}
	tmp = env;
	while (tmp)
	{
		update_value(env, "PWD", pwd);
		tmp = tmp->next;
	}
	if (write == 1)
		printf("%s\n", pwd);
	free(pwd);
	return (0);
}
