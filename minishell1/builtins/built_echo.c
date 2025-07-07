/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:08:32 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/07 15:55:34 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_option(char *str)
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

static char	*build_echo_output(char **argv, int index)
{
	char	*buffer;
	char	*tmp;
	int		i;

	buffer = ft_strdup("");
	if (!buffer)
		return (free(buffer), NULL);
	i = index;
	while (argv && argv[i])
	{
		tmp = buffer;
		if (argv[i + 1])
			buffer = ft_strjoin_3(buffer, argv[i], " ");
		else
			buffer = ft_strjoin(buffer, argv[i]);
		free(tmp);
		if (!buffer)
			return (NULL);
		i++;
	}
	return (buffer);
}

int	ft_echo(char **argv)
{
	int		i;
	int		new_line;
	char	*buffer;
	char	*tmp;

	new_line = 1;
	i = 1;
	if (argv[i] && is_valid_option(argv[i]) == 0)
	{
		new_line = 0;
		i++;
	}
	buffer = build_echo_output(argv, i);
	if (!buffer)
		return (free(buffer), 1);
	if (new_line)
	{
		tmp = buffer;
		buffer = ft_strjoin(buffer, "\n");
		free(tmp);
		if (!buffer)
			return (1);
	}
	write(1, buffer, ft_strlen(buffer));
	return (free(buffer), 0);
}
