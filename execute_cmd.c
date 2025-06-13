/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:17:10 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/13 20:38:39 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

void handle_redirs(t_redir_node *redir)
 {
    int fd;
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
            fd = open (redir->filename, O_CREAT| O_RDWR |O_APPEND, 0644);
            if(fd < 0 || dup2(fd, 1) == -1)
            {
                perror ("append redirection ");
                exit(1);
            }
            close (fd);
        }
        // else if (redir->kind == REDIR_HEREDOC)
        // {
            
        // }
        redir = redir->next;
    }
}

void execute_cmd(t_tree *tree, char **env) {
    pid_t pid;

    char *path = find_cmd_path(tree->argv[0], env);
    if (!path) {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(tree->argv[0], 2);
        ft_putstr_fd(": command not found\n", 2);
    }
    pid = fork();
    if (pid == 0)
    {
        handle_redirs(tree->redirs);
        if (execve(path, tree->argv, env) == -1)
        {
            free(path);
        }
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
    free(path);
}


void execute_pipe(t_tree *tree, char **env)
{
    int pipefd[2];
    pid_t pid_left;
    pid_t pid_right;

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
        exec_tree(tree->left, env);
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
    
    waitpid(pid_left, NULL, 0);
    waitpid(pid_right, NULL, 0);
}

void exec_tree(t_tree *tree, char **env)
{
    if (!tree)
        return ;
    if (tree->kind == NODE_COMMAND)
    {
        execute_cmd(tree, env);
    }
    else if (tree->kind == NODE_PIPE)
    {
        execute_pipe(tree, env);
    }
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
