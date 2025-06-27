/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:06:13 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/27 18:34:05 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_path(char *path)
{
	int i;
	
	if (!path)
		return (1);
	i = 0;
	while(path[i])
	{
		if (path[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
void	put_errno(char *dir) //int
{
	if (is_path(dir) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": command not found\n", 2);
		return ;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": ", 2);
	if (errno == 13)
		ft_putstr_fd("Permission denied\n", 2);
	else if (errno == 2)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (errno == 20)
		ft_putstr_fd("Not a directory\n", 2);
	// else if (errno == EISDIR) //21
	// 	ft_putstr_fd("is a directory\n", 2); check with access
	else
		ft_putstr_fd("command not found\n", 2);
}
