/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0002/01/01 00:00:00 by haqajjef          #+#    #+#             */;
/*   Updated: 2025/05/07 17:12:27 by haqajjef         ###   ######cmd2     */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void execute_2cmd(char **argv, char **env)
{
    int pipefd[2];
    pid_t pid1;
    pid_t pid2;
    char *path1 = find_cmd_path(argv[1], env);
    char *path2 = find_cmd_path(argv[2], env);

    if(!path1 || !path2)
    {
        perror("Commande introuvable!");
        exit(1);
    }
    pipe(pipefd);
    pid1 = fork();
    if (pid1 == 0)
    {
        char *cmd1[] = {argv[1], NULL};
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        close(pipefd[0]); 
        if (execve(path1, cmd1, env) == -1)
		{
			perror("execv");
			free(path1);
			exit(1);
		}
	}
    pid2 =  fork();
    if(pid2 == 0)
    {
        char *cmd2[] = {argv[2], NULL};
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        close(pipefd[0]);
        if (execve(path2, cmd2, env) == -1)
		{
			perror("execv");
			free(path2);
			exit(1);
		}
    }
    close(pipefd[1]);
    close(pipefd[0]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
// int main(int argc, char **argv, char **env)
// {

//     if (argc < 3)
//     {
//         printf("pas suffisant !");
//         return 1;
//     }
//     execute_2cmd(argv, env);
//     return (0);
// }