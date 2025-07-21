/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:47:42 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/21 14:55:04 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dolar(char *delimiter)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (delimiter[i] && delimiter[i] != '"')
	{
		if (delimiter[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*rm_dolar(char *str)
{
	char	*dest;
	int		i;
	char	n;
	int		j;

	i = 0;
	j = 0;
	n = 0;
	dest = ft_malloc(sizeof(ft_strlen(str)));
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && str[i + 1] == '"' && n == 0)
		{
			i++;
			n = 1;
		}
		else
			dest[j++] = str[i++];
	}
	dest[j] = '\0';
	return (dest);
}

char	*handel_dolar(char *delimiter)
{
	if (ft_strnstr(delimiter, "$\"", ft_strlen(delimiter)))
	{
		if (count_dolar(delimiter) % 2 != 0)
			return (rm_dolar(delimiter));
	}
	return (delimiter);
}

void	write_in_herdoc(t_redir_node *redir, t_env *env, int fd)
{
	char	*line;
	char	*line1;

	while (!g_signal)
	{
		line = readline(">");
		line1 = ft_strdup(line);
		redir->filename = rm_quotes(handel_dolar(redir->filename));
		if (!line1 || !ft_strcmp(line1, redir->filename))
		{
			if (line1)
				free(line);
			break ;
		}
		if (redir->flag == 0)
			line1 = trasform_garbeg(expand_heredoc(line1, env, 1));
		ft_putstr_fd(line1, fd);
		write(fd, "\n", 1);
		free(line1);
		free(line);
	}
	close(fd);
}

char	*generate_filename(void)
{
	char		*filename;
	static long	i;
	char		*num;

	num = ft_itoa(i);
	filename = ft_strjoin("/tmp/heredoc_", num);
	if (filename)
		i++;
	free(num);
	return (filename);
}
