/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:08:32 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/19 19:10:15 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s) +1);
}

int	is_valid_option(char *str)
{
	int	i;

	i = 2;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (-1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (-1);
		i++;
	}
	return (1);
}

void	ft_echo(char **argv)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	if (argv[i] && is_valid_option(argv[i]) == 1)
	{
		new_line = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	ft_echo(argv);
	return (0);
}
