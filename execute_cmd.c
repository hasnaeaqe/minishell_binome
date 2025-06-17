/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:17:10 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/17 18:30:31 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"



void handele_heredoc(t_tree *tree)
{
    t_redir_node *redir;
    char *line;
    char *delimited;
    int fd;
    char *lines;

    redir = tree->redirs;
    delimited = redir->filename;
    while(redir)
    {
        if (redir->kind == REDIR_HEREDOC)
        {
        
            while(1)
            {
                line = readline(">");
                if (!line || ft_strcmp(line, delimited))
                {
                    free (line);
                    break;
                }
                line = ft_strjoin(line, "\n");
                lines = ft_strjoin(lines, line);
                unlink("tmp/tmpfile");
                fd = open("tmp/tmpfile", O_CREAT| O_RDWR , 0644);
                ft_putstr_fd(line, fd);
                unlink("tmp/tmpfile");
            }
        }
        close(fd);
        redir = redir->next;
    }
}
void handle_redirs(t_tree *tree)
 {
    t_redir_node *redir;
    int fd;
    
    redir = tree->redirs;
    while (redir)
    {
        if (redir->kind == REDIR_INPUT)
        {
            fd = open (redir->filename, O_RDONLY);
            if (fd < 0 || dup2(fd, 0) == -1)
            {
                perror("input redirection");
                exit(1);
            }
            close (fd);
        }
        else if (redir->kind == REDIR_OUTPUT)
        {
            fd = open (redir->filename, O_CREAT| O_RDWR |O_TRUNC, 0644);
            if (fd < 0 || dup2(fd, 1) == -1)
            {
                perror("output redirection");
                exit(1);
            }
            close (fd);
        }
        else if (redir->kind == REDIR_APPEND)
        {
            fd = open(redir->filename, O_CREAT| O_RDWR |O_APPEND, 0644);
            if(fd < 0 || dup2(fd, 1) == -1)
            {
                perror ("append redirection ");
                exit(1);
            }
            close (fd);
        }
         else if (redir->kind == REDIR_HEREDOC)
        {
            handele_heredoc(tree);
        }

        redir = redir->next;
    }
}

int execute_cmd(t_tree *tree, char **env) {
    
    pid_t pid;
    int status;

    status = 0;
    char *path = find_cmd_path(tree->argv[0], env);
    if (!path) {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(tree->argv[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        return (127);
    }
    pid = fork();
    if (pid == 0)
    {
        handle_redirs(tree);
        if (execve(path, tree->argv, env) == -1)
        {
            free(path);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    free(path);
    return (WEXITSTATUS(status));
}


int execute_pipe(t_tree *tree, char **env)
{
    int pipefd[2];
    pid_t pid_left;
    pid_t pid_right;
    int status;

    status = 0;
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    pid_left = fork();
    if (pid_left == -1)
    {
        perror ("fork left");
        exit(1);
    }
    if (pid_left == 0)
    {
        dup2(pipefd[1], 1);
        close(pipefd[0]); 
        close(pipefd[1]);
        exec_tree(tree->left, env);// should return int (status )
        exit(127);
	}
    pid_right =  fork();
    if (pid_right == -1)
    {
        perror ("fork right");
        exit(1);
    }
    if(pid_right == 0)
    {
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        close(pipefd[0]);
        exec_tree(tree->right, env);
        exit(127);
    }
    close(pipefd[1]);
    close(pipefd[0]);
    
    // waitpid(pid_left, NULL, 0);
    waitpid(pid_right, &status, 0);
    // (wait(NULL)); // while wait didn't return -1 call it again 
    return (WEXITSTATUS(status));
}

int exec_tree(t_tree *tree, char **env)
{
    if (!tree)
        return (0);
    if (tree->kind == NODE_COMMAND)
        return(execute_cmd(tree, env)); 
    else if (tree->kind == NODE_PIPE)
        return (execute_pipe(tree, env));
    return (1);
}


int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*token;
	t_tree	*tree;
	(void)argc;
	(void)argv;
	//atexit(f);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		token = NULL;
		tokenisation(line, &token);
		//print_tokens(token);
		if (check_syntax_errors(token))
		{
			free_tokens(token);
			free(line);
			continue ;
		}
		//expand_tokens(&token);
		tree = parse_tree(&token);
		//print_tree(tree, 0);
		exec_tree(tree, env);
		free_tokens(token);
		free(line);
	}
	return (0);
}
