/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:22 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/27 18:29:27 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	check(int s)
// {
// 	if (s == -1)
// 		return (0);
// 	return (-1);
// }

// int	ft_atoi(const char *str)
// {
// 	int		s;
// 	long	r;
// 	long	tmp;

// 	r = 0;
// 	s = 1;
// 	while (*str == ' ' || (*str >= 9 && *str <= 13))
// 		str++;
// 	if (*str == '+' || *str == '-')
// 	{
// 		if (*str == '-')
// 			s = -1;
// 		str++;
// 	}
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		tmp = r;
// 		r = r * 10 + (*str - '0');
// 		if (r / 10 != tmp)
// 			return (check(s));
// 		str++;
// 	}
// 	return ((int)(s * r));
// }


// int exit_status(int status, int flag)
// {
//     static int static_status;

//     if (flag)
//         return (static_status);
//     static_status = status;
//     return (static_status);
// }

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
	printf("exit\n");
	if (!args)
        exit(0);
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			exit(255);
		}
		if (args[2])
		{
			printf("exit: too many arguments\n");
			return ;
		}
		int	arg = ft_atoi(args[1]);
		// if (arg < 0 || arg > 255)
        // {
        //     printf("exit: %d: invalid exit status\n", arg);
        //     exit(255);
        // }
		exit((unsigned char)arg);
	}
	exit (0);
}

// int	main(int argc, char **argv)
// {
// 	if (argc > 1)
// 		built_exit(argv);
// 	else
// 		built_exit(NULL);
// 	return (0);
// }
