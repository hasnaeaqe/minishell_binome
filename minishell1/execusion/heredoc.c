/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:47:29 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/13 10:08:22 by cbayousf         ###   ########.fr       */
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
	if (tree->kind != NODE_COMMAND)
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
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_IGN);
				close(fdread);
				write_in_herdoc(redir, env, fd);
				exit(0);
			}
			else
			{
				close(fd);
				signal(SIGINT, SIG_IGN);
				waitpid(pid, &status, 0);
				// signal(SIGINT, SIG_DFL);
				if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				{
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



static int handle_input(t_redir_node *redir)
{
	int fd;

	if (redir->ambiguous)
	return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), exit_status(1,0), 1);
	if (redir->ishd == 1)
		fd = redir->fd;
	else
		fd = open(redir->filename, O_RDONLY);
	if (fd < 0 || dup2(fd, 0) == -1)
	{
		perror(redir->filename); 
		return (1);
	}
	close (fd);
	return (0);
}


static int handle_output(t_redir_node *redir)
{
	int fd;

	if (redir->ambiguous==1)
		return (ft_putstr_fd("minishell: ambiguous redirect\n", 2),exit_status(1,0), 1);
	fd = open(redir->filename, O_CREAT |O_RDWR | O_TRUNC ,0644);
	if (fd < 0 || dup2(fd, 1) == -1)
	{
		perror(redir->filename); 
		return (1);
	}
	close (fd);
	return (0);
}
static int handle_append(t_redir_node *redir)
{
	int fd;
	if (redir->ambiguous)
		return (ft_putstr_fd("minishell: ambiguous redirect\n", 2),exit_status(1,0), 1);
	fd = open(redir->filename, O_CREAT| O_RDWR |O_APPEND, 0644);
	if(fd < 0 || dup2(fd, 1) == -1)
	{
		perror(redir->filename); 
		return (1);
	}
	close (fd);
	return (0);
}

int    handle_redirs(t_tree *tree)
{
	t_redir_node *redir;

	redir = tree->redirs;
	while (redir)
	{
		if (redir->kind == REDIR_INPUT)
		{
			if (handle_input(redir))
				return (1);
		}
		else if (redir->kind == REDIR_OUTPUT)
		{
			if (handle_output(redir))
				return (1);
		}
		else if (redir->kind == REDIR_APPEND)
		{
			if (handle_append(redir))
				return (1);
		}
		redir = redir->next;
	}
	return(0);
}
