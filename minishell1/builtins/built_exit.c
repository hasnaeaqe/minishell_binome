/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:22 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/08 20:49:10 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exit_status(int status, int flag)
{
    static int static_status;

    if (flag)
        return (static_status);
    static_status = status;
    return (static_status);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	built_exit(char **args)
{
	int overflow;
	int arg;
	overflow = 0;
	// ft_putstr_fd("exit\n", 2);
	if (!args || !args[1])
        exit(0);
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("numeric argument required\n", 2);
		exit(255);
	}
	arg = ft_atoi(args[1], &overflow);
	if (overflow)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit (255);
	}
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	exit((unsigned char)arg);
}
