/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:08:32 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/26 16:03:55 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s && s[i] != '\0')
// 		i++;
// 	return (i);
// }

void	ft_str(char *s)
{
	write(1, s, ft_strlen(s) +1);
}

int	is_valid_option(char *str)
{
	int	i;

	i = 2;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **argv)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	if (argv[i] && is_valid_option(argv[i]) == 0)
	{
		new_line = 0;
		i++;
	}
	while (argv[i])
	{
		if (argv[i + 1])
			ft_str(ft_strjoin(argv[i], " "));
		else
			ft_str(argv[i]);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}
