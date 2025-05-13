/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:17:10 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/13 15:27:59 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void execute(char **argv, char **env)
{
    int pipefd1[2];
    int pid;
    char *path;
    int i;
    pipe(pipefd1);
    pid = fork();
    i = 1;
    while(argv[i])
    {
        path = find_cmd_path(argv[i], env);
        if(!path)
        {
            perror("Commande introuvable!");
            exit(1);
        }
        if (pid == 0)
        {
            char *cmd1[] = {argv[i], NULL};
            dup2(pipefd1[1], 1);
            close(pipefd1[1]);
            close(pipefd1[0]); 
            if (execve(path, cmd1, env) == -1)
            {
                perror("execv");
                free(path);
                exit(1);
            }
        }
        else
        {
            wait(NULL);
        }
        i++;
    }
}