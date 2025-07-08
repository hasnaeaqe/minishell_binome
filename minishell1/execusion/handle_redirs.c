/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:47:29 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/08 16:06:29 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int count_dolar()
{
	
}
int handel_dolar(char *line, char *delimiter)
{
	if (ft_strnstr(delimiter, "$\"\"",ft_strlen(delimiter)))
	{
		count_dolar();
	}
	
}
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
            unlink("/tmp/tmpfile");  /////access
            int fd = open("/tmp/tmpfile", O_CREAT | O_WRONLY , 0644);
            int fdread = open("/tmp/tmpfile", O_RDONLY, 0644);
            unlink("/tmp/tmpfile");
            redir->fd = fdread;
            while(1)
            {
                line = readline(">");
                if (!line || !ft_strcmp(line, delimiter) || handel_dolar(line, delimiter)) 
                {
                    if (line)
                        free(line);
                    break;
                }
                if (redir->flag == 0)
                    line = expand_heredoc(line, env,1);
                ft_putstr_fd(line, fd);
                write(fd, "\n", 1);    
            }
            redir->kind = REDIR_INPUT;
        }
        redir = redir->next;
    }
    return ; 
}

int    handle_redirs(t_tree *tree)
{
	// puts("ana hona \n");
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
				// put_errno(redir->filename);
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