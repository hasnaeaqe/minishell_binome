/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_to_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:56:39 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/08 14:04:10 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"


void pipe_to_file(char **argv, char **env)
{
    char *path1;
    path1 = find_cmd_path(argv[1], env);
    if(!path1)
    {
        perror("commande introuvable!");
        exit(1);
    }
    pid_t pid1;
    int fd;
    fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    pid1 = fork();
    if(pid1 == 0)
    {
        char  *cmd1[] = {argv[1], NULL};
        dup2(fd, 1);
        close(fd);
        if(execve(path1, cmd1, env) == -1)
        {
            perror("execve");
            exit(1);
        }
    }
    else
    {
        close(fd);
        waitpid(pid1, NULL, 0);
    }
}
// int main(int argc, char **argv, char **env)
// {
//     if(argc < 2)
//     {
//         printf("usage: /cmd/file/");
//         return 1;
//     }
//     pipe_to_file(argv, env);
//     return (0);
// }