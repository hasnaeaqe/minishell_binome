/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:42:46 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/12 11:42:26 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parsing/minishell.h"

// void handle_redirections(t_redir_node *redirs)
// {
//     int fd;
//     if (!redirs)
//         return;
//     while(redirs)
//     {
//         if (redirs ->kind == REDIR_INPUT)
//         {
//             fd = open(redirs->filename, O_RDONLY);
//             if (fd < 0)
//             {
//                 perror("open");
//                 exit(1);
//             }
//             dup2(fd, STDIN_FILENO);
//             close(fd);
//         }
//         else if (redirs ->kind == REDIR_OUTPUT)
//         {
//             fd = open(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (fd < 0)
//             {        
//                 perror("open");
//                 exit(1);
//             }
//             dup2(fd, STDOUT_FILENO);
//             close(fd);
//         }
//         else if (redirs ->kind == REDIR_APPEND)
//         {
//             fd = open(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
//             dup2(fd, STDOUT_FILENO);
//             close(fd);
//         }
//         // else if (redirs ->kind == REDIR_HEREDOC)
//         // {
    
//         // }
//         redirs = redirs->next;
//     }
// }


// // void execute_cmd(t_tree *tree, char **argv, char **env)
// // {
// //     pid_t pid;
// //     char *path;
// //     pid = fork();
// //     if(pid == 0)
// //     {
// //         path = find_cmd_path(argv[0], env);
// //     }
// // }
// void exec_tree(t_tree *tree, char **env)
// {
//     if (!tree)
//         return;
//     if (tree->kind == NODE_COMMAND)
//     {
//         pid_t pid = fork();
//         if(pid == 0)
//         {
//             handle_redirections (tree->redirs);
//             char *path = find_cmd_path(tree->argv[0], env);
//             if (!path)
//             {
//                 perror("commande introuvable!");
//                 exit(1);
//             }
//             if (execve(path, tree->argv, env) == -1)
//             {
//                 perror("execve");
//                 free(path);
//                 exit(1);
//             }
//         }
//         else
//         {
//             wait(NULL);
//             //waitpid(pid, NULL, 0);
//         }
//     }
//     else if (tree->kind == NODE_PIPE)
//     {
//         int pipefd[2];
//         pipe(pipefd);

//         pid_t left_pid = fork();
//         if (left_pid == 0)
//         {
//             dup2(pipefd[1] , STDOUT_FILENO);
//             close(pipefd[0]);
//             close(pipefd[1]);
//             exec_tree(tree->left, env);
//             exit(0);
//         }

//         pid_t right_pid = fork();
//         if (right_pid == 0)
//         {
//             dup2(pipefd[1] , STDIN_FILENO);
//             close(pipefd[0]);
//             close(pipefd[1]);
//             exec_tree(tree->right, env);
//             exit(0);
//         }
//         close(pipefd[1]);
//         close(pipefd[0]);
//         waitpid(left_pid, NULL, 0);
//         waitpid(right_pid, NULL, 0);
//     }
// }

// t_token *parse_input(char *input)
// {
//     t_token *tokens = NULL;
//     tokenisation(input, &tokens);
//     if (check_syntax_errors(tokens))
//     {
//         free_tokens(tokens);
//         return NULL;
//     }
//     return tokens;
// }
// int main(int argc, char **argv, char **env)
// {
//     if  (argc < 2)
//     {
//         printf("Usage: %s <command>\n", argv[0]);
//         return 1;
//     }
//     t_token *tokens = parse_input(argv[1]);
//     t_tree *tree = parse_tree(&tokens);
//     exec_tree(tree, env);
//     return (0);
// }

// // int main(int argc, char **argv, char **envp)
// // {
// //     t_token *tokens = NULL;
// //     t_tree *tree;

// //     if (argc < 2)
// //     {
// //         printf("Usage: %s \"<commande>\"\n", argv[0]);
// //         return 1;
// //     }

// //     tokenisation(argv[1], &tokens);
// //     print_tokens(tokens);

// //     if (check_syntax_errors(tokens))
// //     {
// //         free_tokens(tokens);
// //         return 1;
// //     }
// //     tree = parse_tree(&tokens);
// //     print_tree(tree, 0);

// //     exec_tree(tree, envp);

// //     free_tokens(tokens);
// //     return 0;
// // }


#include "parsing/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>



/* Gère les redirections de fichiers pour une commande */
void handle_redirections(t_redir_node *redirs)
{
    int fd;

    while (redirs)
    {
        if (redirs->kind == REDIR_INPUT)
        {
            fd = open(redirs->filename, O_RDONLY);
            if (fd < 0 || dup2(fd, STDIN_FILENO) == -1)
            {
                perror("input redirection");
                exit(1);
            }
            close(fd);
        }
        else if (redirs->kind == REDIR_OUTPUT)
        {
            fd = open(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("output redirection");
                exit(1);
            }
            close(fd);
        }
        else if (redirs->kind == REDIR_APPEND)
        {
            fd = open(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("append redirection");
                exit(1);
            }
            close(fd);
        }
        // else if (redirs->kind == REDIR_HEREDOC)
        // {
        //     // Gérer les here-docs ici si tu les implémentes
        // }

        redirs = redirs->next;
    }
}

/* Exécute récursivement l’arbre d’exécution */
void exec_tree(t_tree *tree, char **env)
{
    if (!tree)
        return;

    if (tree->kind == NODE_COMMAND)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return;
        }

        if (pid == 0) // Processus enfant
        {
            handle_redirections(tree->redirs);

            char *path = find_cmd_path(tree->argv[0], env);
            if (!path)
            {
                fprintf(stderr, "%s: command not found\n", tree->argv[0]);
                exit(127);
            }

            if (execve(path, tree->argv, env) == -1)
            {
                perror("execve");
                free(path);
                exit(1);
            }
        }
        else
        {
            waitpid(pid, NULL, 0);
        }
    }
    else if (tree->kind == NODE_PIPE)
    {
        int pipefd[2];
        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            exit(1);
        }

        pid_t left_pid = fork();
        if (left_pid == -1)
        {
            perror("fork left");
            exit(1);
        }

        if (left_pid == 0)
        {
            dup2(pipefd[1], STDOUT_FILENO); // gauche écrit dans pipe
            close(pipefd[0]);
            close(pipefd[1]);
            exec_tree(tree->left, env);
            exit(0);
        }

        pid_t right_pid = fork();
        if (right_pid == -1)
        {
            perror("fork right");
            exit(1);
        }

        if (right_pid == 0)
        {
            dup2(pipefd[0], STDIN_FILENO); // droite lit du pipe
            close(pipefd[0]);
            close(pipefd[1]);
            exec_tree(tree->right, env);
            exit(0);
        }

        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(left_pid, NULL, 0);
        waitpid(right_pid, NULL, 0);
    }
}

/* Fonction utilitaire pour concaténer tous les arguments */
char *join_args(char **args)
{
    size_t total_len = 0;
    int i = 0;
    while (args[i])
    {
        total_len += strlen(args[i]) + 1; // +1 pour l'espace
        i++;
    }

    char *result = malloc(total_len + 1); // +1 pour '\0'
    if (!result)
        return NULL;

    result[0] = '\0';
    for (int j = 0; args[j]; j++)
    {
        strcat(result, args[j]);
        if (args[j + 1])
            strcat(result, " ");
    }
    return result;
}
// free_args.c ou utils.c
void free_args(char **args)
{
    int i = 0;
    if (!args) return;
    while (args[i])
        free(args[i++]);
    free(args);
}

// free_redirs.c ou utils.c
void free_redirs(t_redir_node *redir)
{
    t_redir_node *tmp;
    while (redir)
    {
        tmp = redir;
        redir = redir->next;
        free(tmp->filename);
        free(tmp);
    }
}


void free_tree(t_tree *tree)
{
    if (!tree)
        return;
    if (tree->left)
        free_tree(tree->left);
    if (tree->right)
        free_tree(tree->right);
    free_args(tree->argv);
    free_redirs(tree->redirs);
    free(tree);
}

/* Tokenise l'entrée, vérifie la syntaxe et retourne les tokens */
t_token *parse_input(char *input)
{
    t_token *tokens = NULL;
    tokenisation(input, &tokens);
    if (check_syntax_errors(tokens))
    {
        free_tokens(tokens);
        return NULL;
    }
    return tokens;
}

// int main(int argc, char **argv, char **env)
// {
//     if (argc < 2)
//     {
//         printf("Usage: %s <command>\n", argv[0]);
//         return 1;
//     }

//     char *input = join_args(argv + 1);
//     if (!input)
//     {
//         perror("join_args");
//         return 1;
//     }

//     t_token *tokens = parse_input(input);
//     free(input);

//     if (!tokens)
//         return 1;

//     t_tree *tree = parse_tree(&tokens);
//     if (!tree)
//     {
//         free_tokens(tokens);
//         return 1;
//     }

//     exec_tree(tree, env);

//     free_tree(tree);
//     free_tokens(tokens);
//     return 0;
// }
