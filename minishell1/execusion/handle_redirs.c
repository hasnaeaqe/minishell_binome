/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:47:29 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/10 20:48:41 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

// int count_dolar()
// {
	
// }
// int handel_dolar(char *line, char *delimiter)
// {
// 	if (ft_strnstr(delimiter, "$\"\"",ft_strlen(delimiter)))
// 	{
// 		count_dolar();
// 	}
	
// }
void handle_heredoc(t_tree *tree, t_env *env)
{
    t_redir_node *redir;
    char    *line;
    char    *delimiter;

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
        delimiter = redir->filename;
        redir->ishd = 0;
        if (redir->kind == REDIR_HEREDOC)
        {
            redir->ishd = 1;
			if (access("/tmp/tmpfile", F_OK) == 0)
            	unlink("/tmp/tmpfile"); 
            int fd = open("/tmp/tmpfile", O_CREAT | O_WRONLY | O_APPEND , 0644);
			if (fd == -1)
			{
				perror("heredoc open write");
				return ;
			}
            int fdread = open("/tmp/tmpfile", O_RDONLY, 0644);
			if (fdread == -1)
			{
				perror("heredoc open (read)");
				close(fd);
				return;
			}
            unlink("/tmp/tmpfile");
            redir->fd = fdread;
            while(1)
            {
                line = readline(">");
                if (!line || !ft_strcmp(line, delimiter)) 
                {
                    if (line)
                        free(line);
                    break;
                }
                if (redir->flag == 0)
                    line = expand_heredoc(line, env,1);
                ft_putstr_fd(line, fd);
                write(fd, "\n", 1);
				free (line);
            }
			close(fd);
            redir->kind = REDIR_INPUT;
        }
        redir = redir->next;
    }
    return ; 
}


int    handle_redirs(t_tree *tree)
{
	t_redir_node *redir;
	int fd;
	
	redir = tree->redirs;
	while (redir)
	{
		if (redir->kind == REDIR_INPUT)
		{
			if (redir->ishd == 1)
				fd = redir->fd;
			else
			{
				if (redir->ambiguous==1)
				{
					ft_putstr_fd("minishell: ambiguous redirect\n", 2);
					exit_status(1,0);
					return (1);
				}
				else
					fd = open (redir->filename, O_RDONLY);
			}
			if (fd < 0 || dup2(fd, 0) == -1)
			{
				// perror("input redirection");
				// ft_putstr_fd("minishell: ", 2);
				// ft_putstr_fd(redir->filename, 2);
				// ft_putstr_fd(": No such file or directory\n", 2);
				return (1);
			}
			close (fd);
		}
		else if (redir->kind == REDIR_OUTPUT)
		{
			if (redir->ambiguous==1)
			{
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				exit_status(1,0);
				return (1);
			}
			else
				fd = open (redir->filename, O_CREAT| O_RDWR |O_TRUNC, 0644);
			if (fd < 0 || dup2(fd, 1) == -1)
			{
				// perror("output redirection"); // 
				return (1);
			}
			close (fd);
		}
		else if (redir->kind == REDIR_APPEND)
		{
			if (redir->ambiguous==1)
			{
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				exit_status(1,0);
				return (1);
			}
			else
				fd = open(redir->filename, O_CREAT| O_RDWR |O_APPEND, 0644);
			if(fd < 0 || dup2(fd, 1) == -1)
			{
				perror ("append redirection ");
				return (1);
			}
			close (fd);
		}
		redir = redir->next;
	}
	return (0);
}
