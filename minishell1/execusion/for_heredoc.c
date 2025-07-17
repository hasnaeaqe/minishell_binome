/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:47:42 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/17 14:53:47 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dolar(char *delimiter)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*handel_dolar(char *delimiter, int flag)
{
	if (flag == 1)
	{
		if (count_dolar(delimiter) % 2 != 0)
			return (ft_strdup(&delimiter[1]));
	}
	return (delimiter);
}

void	write_in_herdoc(t_redir_node *redir, t_env *env, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line)
		{
			close(fd);
			exit (1);
		}
		redir->filename = handel_dolar(redir->filename, redir->flag);
		if (!line || !ft_strcmp(line, redir->filename))
		{
			if (line)
				free(line);
			break ;
		}
		if (redir->flag == 0)
			line = trasform_garbeg(expand_heredoc(line, env, 1));
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free (line);
	}
	close(fd);
}

char	*generate_filename(void)
{
	char	*filename;
	long	i;
	char	*num;

	i = 0;
	num = ft_itoa(i);
	filename = ft_strjoin("/tmp/heredoc_", num);
	while (access(filename, F_OK) == 0)
	{
		free(filename);
		free(num);
		i++;
		num = ft_itoa(i);
		filename = ft_strjoin("/tmp/heredoc_", num);
	}
	free(num);
	return (filename);
}
