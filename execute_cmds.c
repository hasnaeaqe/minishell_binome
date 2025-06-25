/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:59:31 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/12 12:21:11 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

void exec_cmd(int argc, char **argv, char **env){
    
    if (argc < 2)
    {
        return ;
    }
    int i;
    pid_t pid;
    char *path;
    
    i = 1;
    int pipefd[2];
    while(argv[i])
    {
        pipe(pipefd);
        pid = fork();
        
        if (pid == 0)
        {
            path = find_cmd_path(argv[i], env);
            if (!path)
            {
                // printf("error command not found");
                exit(1);
            }
            char *cmd[] = {argv[i], NULL};
            if(i < argc - 1)
            {
                dup2(pipefd[1], 1);
                close(pipefd[1]);
                close(pipefd[0]);
            }
            if (execve(path, cmd, env) == -1)
            {
                perror("execve");
                free(path);
                exit(1);
            }
            
        }
        waitpid(pid, NULL, 0);
        close(pipefd[1]);
        close(pipefd[0]);
        i++;
    }
}
    


int main(int argc, char **argv, char **env)
{
    exec_cmd(argc, argv, env);
    return 0;
}