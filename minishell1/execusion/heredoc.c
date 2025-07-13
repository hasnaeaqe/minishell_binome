/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:47:29 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/13 14:41:06 by haqajjef         ###   ########.fr       */
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
		redir->filename = handel_dolar(redir->filename, redir->flag);
		if (!line || !ft_strcmp(line, redir->filename))
		{
			if (line)
				free(line);
			break ;
		}
		if (redir->flag == 0)
			line = expand_heredoc(line, env, 1);
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free (line);
	}
	close(fd);
}
char *generate_filename(void)
{
	char *filename;
	long i;
	char *num;

	i = 0;
	num = ft_itoa(i);
	filename = ft_strjoin("/tmp/heredoc_",num);
	while(access(filename, F_OK) == 0)
	{
		free(filename);
		free(num);
		i++;
		num = ft_itoa(i);
		filename = ft_strjoin("/tmp/heredoc_",num);
	}
	free(num);
	return (filename);
}

void handle_heredoc(t_tree *tree, t_env *env)
{
	t_redir_node *redir;
	pid_t pid;
	int fd;
	int status;
	int fdread;
	char *filename;

	if (!tree)
		return ;
	if (tree->kind == NODE_PIPE)
	{
		handle_heredoc(tree->left,env);
		handle_heredoc(tree->right,env);
		return ;
	}
	redir = tree->redirs;
	while (redir)
	{
		redir->ishd = 0;
		if (redir->kind == REDIR_HEREDOC)
		{
			redir->ishd = 1;
			filename = generate_filename();
			fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("heredoc open write");
				return ;
			}
			fdread = open(filename, O_RDONLY, 0644);
			if (fdread == -1)
			{
				perror("heredoc open read");
				return ;
			}
			unlink(filename);
			free(filename);
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				return;
			}
			
			if (pid == 0)
			{
				signal(SIGINT, handle_heredoc_sigint);
				signal(SIGQUIT, SIG_IGN);
				close(fdread);
				write_in_herdoc(redir, env, fd);
				exit(0);
			}
			else
			{
				close(fd);
				void (*old_handler)(int);
				old_handler = signal(SIGINT, SIG_IGN);
				waitpid(pid, &status, 0);
				signal(SIGINT, old_handler);
				if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				{
					write(1, "\n", 1);
					exit_status(130, 0);
					free(filename);
					return;
				}
				exit_status(0, 0);
				redir->fd = fdread;
				redir->kind = REDIR_INPUT;
			}
		}
	// {
	// 	perror("pipe");
	// 	exit(1);// exit if in child
	// }
	// handle_heredoc(tree->left, env);
	// handle_heredoc(tree->r
		redir = redir->next;
	}
	return ; 
}

