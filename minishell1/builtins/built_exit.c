/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:22 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/14 18:46:21 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_status(int status, int flag)
{
	static int	static_status;

	if (flag)
		return (static_status);
	static_status = status;
	return (static_status);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (str[i] == '\0');
}

static void	args_required(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	built_exit(char **args, int is_child)
{
	int			overflow;
	long long	arg;

	overflow = 0;
	if (!is_child)
		ft_putstr_fd("exit\n", 2);
	if (!args || !args[1])
		exit(0);
	if (!is_numeric(args[1]))
		return(args_required(args[1]), 255);
	arg = ft_atoi(args[1], &overflow);
	if (overflow)
	{
		args_required(args[1]);
		exit(255);
	}
	if (arg < 0 || arg > 255)
		arg = arg % 256;
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	exit((unsigned char)arg);
}
