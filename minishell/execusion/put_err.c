/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:06:13 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/27 13:12:58 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_errno(char *dir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": ", 2);
	if (errno == 13)
		ft_putstr_fd("Permission denied\n", 2);
	else if (errno == 2)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (errno == 20)
		ft_putstr_fd("Not a directory\n", 2);
	else if (errno == 0)
		ft_putstr_fd("command not found\n", 2);
}
// int is_path(char *path)
// {
// 	int i;

// 	i = 0;
// 	while(path[i])
// 	{
// 		if ()
// 	}
	
// }