/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:22 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/20 10:18:22 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	status_exit(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write (1, "\n", 1);
			return (130);
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			write(1, "Quit: 3\n", 8);
			return (131);
		}
	}
	return (WEXITSTATUS(status));
}

int	exit_status(int status, int i)
{
	static int	s_status;

	if (i)
		return (s_status);
	s_status = status;
	return (s_status);
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
	exit (255);
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
		args_required(args[1]);
	arg = ft_atoi(args[1], &overflow);
	if (overflow)
		args_required(args[1]);
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	exit((unsigned char)arg);
}
