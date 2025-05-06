/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:22 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/06 15:28:33 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

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
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", args[1]);
			exit(255);
		}
		if (args[2])
		{
			fprintf(stderr, "exit: too many arguments\n");
			return ;
		}
		exit(ft_atoi(args[1]));
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
