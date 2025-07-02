/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:17:10 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/02 20:46:49 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
                if (redir->flag == 0)
                    line = expand_heredoc(line, env);
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
				fd = redir->fd;
			else
				fd = open (redir->filename, O_RDONLY);
			if (fd < 0 || dup2(fd, 0) == -1)
			{
				// perror("input redirection");
				put_errno(redir->filename);
				// ft_putstr_fd("minishell: ", 2);
				// ft_putstr_fd(redir->filename, 2);
				// ft_putstr_fd(": No such file or directory\n", 2);
				return (1);
			}
			close (fd);
		}
		else if (redir->kind == REDIR_OUTPUT)
		{
			fd = open (redir->filename, O_CREAT| O_RDWR |O_TRUNC, 0644);
			if (fd < 0 || dup2(fd, 1) == -1)
			{
				perror("output redirection");
				return (1);
			}
			close (fd);
		}
		else if (redir->kind == REDIR_APPEND)
		{
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

char *ft_strjoin_3(char *s1, char *s2, char *s3)
{
    char *tmp;
    char *res;

    tmp = ft_strjoin(s1, s2);
    res = ft_strjoin(tmp, s3);
    free(tmp);
    return res;
}

char **to_array(t_env *env, int size)
{
    char **array;
    t_env *tmp;
    int i;

    array = ft_malloc(sizeof(char *) * (size + 1));
    tmp = env;
    i = 0;
    while (i < size && tmp)
    {
        array[i] = ft_strjoin_3(tmp->key, "=", tmp->value);
        tmp = tmp->next;
        i++;
    }
    array[i] = NULL;
    return (array);
}

int		relative_or_absolute_path(const char *path) {
	int i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int execute_cmd(t_tree *tree, t_env **env) {
	
	pid_t pid;
	int status;
	char **array;

	status = 0;
	array = to_array(*env, ft_lstsize(*env));
	if (tree && is_builtins(*tree->argv) == 1)
		return (check_builts(tree, env));
	char *path = find_cmd_path(tree->argv[0], *env);
	if (!path || (is_directory(path) && !relative_or_absolute_path(tree->argv[0])))
	{
		errors(tree->argv[0], 33);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		puts("ana hona \n ");
		handle_redirs(tree);
		if (tree->argv && tree->argv[0] && execve(path, tree->argv, array) == -1)
			exit (EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &status, 0);
	free(path);
	return (WEXITSTATUS(status));
}

int execute_pipe(t_tree *tree, t_env *env)
{
	int pipefd[2];
	pid_t pid_left;
	pid_t pid_right;
	int status;

	status = 0;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		// exit(1);
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
		exec_tree(tree->left, &env);// should return int (status )
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
		exec_tree(tree->right, &env);
		exit(127);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	
	waitpid(pid_left, NULL, 0); 
	waitpid(pid_right, &status, 0);
	// (wait(NULL)); // while wait didn't return -1 call it again 
	return (WEXITSTATUS(status));
}

int exec_tree(t_tree *tree, t_env **env)
{
	if (!tree)
		return (1);
	if (tree->kind == NODE_COMMAND)
		return(execute_cmd(tree, env));
	else if (tree->kind == NODE_PIPE)
		return (execute_pipe(tree, *env));
	return (0);
}
