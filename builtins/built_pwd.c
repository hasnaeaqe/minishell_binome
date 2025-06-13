/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:34 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/13 21:46:38 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	built_pwd(void)
{
	char	buff[1024];
	char	*cwd;

	cwd = getcwd(buff, sizeof(buff));
	if (cwd == NULL)
	{
		perror("operation echoue!");
	}
	else
	{
		ft_putstr(cwd);
		write(1, "\n", 1);
	}
}

// int	main(void)
// {
// 	ft_pwd();
// 	return (1);
// }
