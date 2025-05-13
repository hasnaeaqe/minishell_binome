/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:29:09 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/13 21:34:33 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void exec_tree(t_tree *tree)
{
    if (!tree)
        return;

    if (tree->kind == NODE_COMMAND)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            // Gérer les redirections ici
            handle_redirections(tree->redirs);

            // Executer la commande
            execvp(tree->argv[0], tree->argv);
            perror("execvp");
            exit(1);
        }
        else
        {
            wait(NULL); // Attendre la fin du fils
        }
    }
    else if (tree->kind == NODE_PIPE)
    {
        int fd[2];
        pipe(fd);

        pid_t left_pid = fork();

        if (left_pid == 0)
        {
            // Fils gauche : écrit dans le pipe
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            exec_tree(tree->left);
            exit(0);
        }

        pid_t right_pid = fork();

        if (right_pid == 0)
        {
            // Fils droit : lit depuis le pipe
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);
            exec_tree(tree->right);
            exit(0);
        }

        // Père ferme les extrémités du pipe et attend
        close(fd[0]);
        close(fd[1]);
        waitpid(left_pid, NULL, 0);
        waitpid(right_pid, NULL, 0);
    }
}

extern char **environ;
execve(tree->argv[0], tree->argv, environ);