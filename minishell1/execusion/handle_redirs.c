/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:47:29 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/12 19:40:48 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int count_dolar(char *delimiter)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (delimiter[i])
	{
		if (delimiter[i]=='$')
			count++;
		i++;
	}
	return (count);
}
char *handel_dolar(char *delimiter,int flag)
{
	if (flag == 1)
	{
		if (count_dolar(delimiter)%2!=0)
			return (ft_strdup(&delimiter[1]));
	}
	return (delimiter);
}

void write_in_herdoc(t_redir_node * redir, t_env *env, int fd)
{
    char *line;

    while(1)
    {
        line = readline(">");
        if (!line || !ft_strcmp(line, redir->filename)) 
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
}
char *generate_filename(void)
{
	char *id;
	char *filename;

	id = ft_itoa(getpid());
	if (!id)
		return (NULL);
	filename = ft_strjoin("/tmp/file_herdoc",id);
	if (!filename)
		return (free(id), NULL);
	free(id);
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
			if (!filename)
				return ;
            pid = fork();
            if (pid == -1)
            {
                perror("fork");
                free(filename);
                return;
            }

            if (pid == 0)
            {
                fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd == -1)
                {
                    perror("heredoc open write");
                    exit(1);
                }
                write_in_herdoc(redir, env, fd);
                exit(0);
            }
            else
            {
                waitpid(pid, &status, 0);
                fdread = open(filename, O_RDONLY, 0644);
                if (fdread == -1)
                {
                    perror("heredoc open (read)");
                    free(filename);
                    return;
                }
                unlink(filename);
                free(filename);
                redir->fd = fdread;
                redir->kind = REDIR_INPUT;
            }
        }
        redir = redir->next;
    }
    return ; 
}

// void handle_heredoc(t_tree *tree, t_env *env)
// {
//     t_redir_node *redir;
//     char    *line;
//     char    *delimiter;

//     if (!tree)
//         return ;
//     if (tree->kind != NODE_COMMAND)
//     {
//         handle_heredoc(tree->left,env);
//         handle_heredoc(tree->right,env);
//         return ;
//     }
//     redir = tree->redirs;
//     while (redir)
//     {
//         delimiter = redir->filename;
//         redir->ishd = 0;
//         if (redir->kind == REDIR_HEREDOC)
//         {
//             redir->ishd = 1;
// 			//fork
// 			//if in child open ecrire.... else{waitpid fdreadici et unlink(filename) redir.fd et redir.kind }
// 			if (access("/tmp/tmpfile", F_OK) == 0)
//             	unlink("/tmp/tmpfile"); 
//             int fd = open("/tmp/tmpfile", O_CREAT | O_WRONLY | O_APPEND , 0644);
// 			if (fd == -1)
// 			{
// 				perror("heredoc open write");
// 				return ;
// 			}
//             int fdread = open("/tmp/tmpfile", O_RDONLY, 0644);
// 			if (fdread == -1)
// 			{
// 				perror("heredoc open (read)");
// 				close(fd);
// 				return;
// 			}
//             unlink("/tmp/tmpfile");
//             redir->fd = fdread;
//             while(1)
//             {
//                 line = readline(">");
					// delimiter = handel_dolar(delimiter, redir->flag);
//                 if (!line || !ft_strcmp(line, delimiter)) 
//                 {
//                     if (line)
//                         free(line);
//                     break;
//                 }
//                 if (redir->flag == 0)
//                     line = expand_heredoc(line, env,1);
//                 ft_putstr_fd(line, fd);
//                 write(fd, "\n", 1);
// 				free (line);
//             }
// 			close(fd);
//             redir->kind = REDIR_INPUT;
//         }
//         redir = redir->next;
//     }
//     return ; 
// }

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


// int    handle_redirs(t_tree *tree)
// {
// 	t_redir_node *redir;
// 	int fd;
	
// 	redir = tree->redirs;
// 	while (redir)
// 	{
// 		if (redir->kind == REDIR_INPUT)
// 		{
// 			if (redir->ishd == 1)
// 				fd = redir->fd;
// 			else
// 			{
// 				if (redir->ambiguous==1)
// 				{
// 					ft_putstr_fd("minishell: ambiguous redirect\n", 2);
// 					exit_status(1,0);
// 					return (1);
// 				}
// 				else
// 					fd = open (redir->filename, O_RDONLY);
// 			}
// 			if (fd < 0 || dup2(fd, 0) == -1)
// 			{
// 				perror(redir->filename); 
// 				// ft_putstr_fd("minishell: ", 2);
// 				// ft_putstr_fd(redir->filename, 2);
// 				// ft_putstr_fd(": No such file or directory\n", 2);
// 				return (1);
// 			}
// 			close (fd);
// 		}
// 		else if (redir->kind == REDIR_OUTPUT)
// 		{
// 			if (redir->ambiguous==1)
// 			{
// 				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
// 				exit_status(1,0);
// 				return (1);
// 			}
// 			else
// 				fd = open (redir->filename, O_CREAT| O_RDWR |O_TRUNC, 0644);
// 			if (fd < 0 || dup2(fd, 1) == -1)
// 			{
// 				perror(redir->filename); 
// 				return (1);
// 			}
// 			close (fd);
// 		}
// 		else if (redir->kind == REDIR_APPEND)
// 		{
// 			if (redir->ambiguous==1)
// 			{
// 				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
// 				exit_status(1,0);
// 				return (1);
// 			}
// 			else
// 				fd = open(redir->filename, O_CREAT| O_RDWR |O_APPEND, 0644);
// 			if(fd < 0 || dup2(fd, 1) == -1)
// 			{
// 				perror(redir->filename); 
// 				return (1);
// 			}
// 			close (fd);
// 		}
// 		redir = redir->next;
// 	}
// 	return (0);
// }
