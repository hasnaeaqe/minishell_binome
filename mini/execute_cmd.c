/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:17:10 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/21 15:48:49 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

int check_builts(t_tree *tree, )
{
    char **cmd;

    if (!tree)
        return (1);
    cmd = tree->argv;
    if (ft_strcmp(*cmd, "cd") == 0)
        return (ft_cd(cmd, ));
    if (ft_strcmp(*cmd, "echo")== 0)
        ft_echo(cmd);
    else if (ft_strcmp(*cmd, "pwd")== 0)
        built_pwd();
    else if (ft_strcmp(cmd, "unset")== 0)
        ft_unset(cmd);
    else if (ft_strcmp(cmd, "echo")== 0)
        ft_echo(cmd);
	return (0);
}
int is_builtins(char *cmd)
{
	if (!cmd || ft_strcmp(cmd, "cd") != 0 || ft_strcmp(cmd, "echo") != 0
	|| ft_strcmp(cmd, "pwd") != 0)
		return (1);
	return (0);
}
void handle_heredoc(t_tree *tree)
{
	t_redir_node *redir;
	char    *line;
	char    *delimiter;

	if (!tree)
		return ;
	if (tree->kind != NODE_COMMAND || !tree->redirs)
	{
		handle_heredoc(tree->left);
		handle_heredoc(tree->right);
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
			unlink("/tmp/tmpfile");
			int fd = open("/tmp/tmpfile", O_CREAT | O_WRONLY , 0644);
			int fdread = open("/tmp/tmpfile", O_RDONLY, 0644);
			unlink("/tmp/tmpfile");
			redir->fd = fdread;
			while(1)
			{
				line = readline(">");
				if (!line || ft_strcmp(line, delimiter) == 0) 
				{
					if (line)
						free(line);
					break;
				}
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
	t_redir_node *redir;
	int fd;
	
	redir = tree->redirs;
	while (redir)
	{
		if (redir->kind == REDIR_INPUT)
		{
			if (redir->ishd == 1)
			{
				fd = redir->fd;
			}
			else
			{
				fd = open (redir->filename, O_RDONLY);
			}
			if (fd < 0 || dup2(fd, 0) == -1)
			{
				// perror("input redirection");
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(redir->filename, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
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
		redir = redir->next;
	}
	return (0);
}

int execute_cmd(t_tree *tree, char **env) {
	
	pid_t pid;
	int status;

	status = 0;
	if (!tree && is_builtins(*tree->argv) == 0)
	{
		return (check_builts(tree));
	}
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
			perror("execve failed :");
			exit(1);
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
	
	waitpid(pid_left, NULL, 0); 
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
	return (0);
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
		// print_tree(tree, 0);
		handle_heredoc(tree);
		exec_tree(tree, env);
		free_tokens(token);
		free(line);
	}
	return (0);
}
