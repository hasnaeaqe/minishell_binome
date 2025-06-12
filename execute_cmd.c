/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:17:10 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/12 20:50:15 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

// void execute_cmd(char **argv, char **env)
// {
//     int pipefd1[2];
//     int pid;
//     char *path;
//     pipe(pipefd1);
//     pid = fork();
//         path = find_cmd_path(argv[1], env);
//         if(!path)
//         {
//             perror("Commande introuvablehhhh!");
//             exit(1);
//         }
//         if (pid == 0)
//         {
//             char *cmd1[] = {argv[1], NULL};
//             dup2(pipefd1[1], 1);
//             close(pipefd1[1]);
//             close(pipefd1[0]); 
//             if (execve(path, cmd1, env) == -1)
//             {
//                 perror("execv");
//                 free(path);
//                 exit(1);
//             }
//         }
//         else
//         {
//             wait(NULL);
//         }
// }

void handle_redirs(t_tree *tree)
{
    int fd;
    if (tree->redirs == REDIR_INPUT)
    {
        fd = open (tree->redirs->filename);
    }
    else if (tree->redirs == REDIR_OUTPUT)
    {
        
    }
    else if (tree->redirs == REDIR_APPEND)
    {
        
    }
    else if (tree->redirs == REDIR_HEREDOC)
    {
        
    }
    
}

void execute_cmd(char **argv, char **env) {
    char *path = find_cmd_path(argv[0], env);
    if (!path) {
        perror("Commande introuvable");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == 0) {
        if (execve(path, argv, env) == -1) {
            perror("execve");
            free(path);
            exit(1);
        }
    } else {
        waitpid(pid, NULL, 0);
    }
    free(path);
}


void execute_pipe(t_tree *tree, char **env)
{
    int pipefd[2];
    pid_t pid_left;
    pid_t pid_right;

    pipe(pipefd);
    pid_left = fork();
    if (pid_left == 0)
    {
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        close(pipefd[0]); 
        exec_tree(tree->left, env);
	}
    pid_right =  fork();
    if(pid_right == 0)
    {
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        close(pipefd[0]);
        exec_tree(tree->right, env);
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
        execute_cmd(tree->argv, env);
    }
    else if (tree->kind == NODE_PIPE)
    {
        execute_pipe(tree, env);
    }
}
// int main(int argc, char **argv, char **env)
// {
//     t_tree *tree;
//     tree = parse_tree(token);
//     exec_tree(tree, env);
// }


// int	main(int argc, char **argv, char **env)
// {
// 	char	*line;
// 	t_token	*token;
// 	t_tree	*tree;
// 	(void)argc;
// 	(void)argv;
// 	//atexit(f);
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 			break ;
// 		if (*line)
// 			add_history(line);
// 		token = NULL;
// 		tokenisation(line, &token);
// 		//print_tokens(token);
// 		if (check_syntax_errors(token))
// 		{
// 			free_tokens(token);
// 			free(line);
// 			continue ;
// 		}
// 		//expand_tokens(&token);
// 		tree = parse_tree(&token);
// 		//print_tree(tree, 0);
// 		exec_tree(tree, env);
// 		free_tokens(token);
// 		free(line);
// 	}
// 	return (0);
// }

// /* Fonction utilitaire pour concaténer tous les arguments */
// char *join_args(char **args)
// {
//     size_t total_len = 0;
//     int i = 0;
//     while (args[i])
//     {
//         total_len += strlen(args[i]) + 1; // +1 pour l'espace
//         i++;
//     }

//     char *result = malloc(total_len + 1); // +1 pour '\0'
//     if (!result)
//         return NULL;

//     result[0] = '\0';
//     for (int j = 0; args[j]; j++)
//     {
//         strcat(result, args[j]);
//         if (args[j + 1])
//             strcat(result, " ");
//     }
//     return result;
// }
// // free_args.c ou utils.c
// void free_args(char **args)
// {
//     int i = 0;
//     if (!args) return;
//     while (args[i])
//         free(args[i++]);
//     free(args);
// }

// // free_redirs.c ou utils.c
// void free_redirs(t_redir_node *redir)
// {
//     t_redir_node *tmp;
//     while (redir)
//     {
//         tmp = redir;
//         redir = redir->next;
//         free(tmp->filename);
//         free(tmp);
//     }
// }


// void free_tree(t_tree *tree)
// {
//     if (!tree)
//         return;
//     if (tree->left)
//         free_tree(tree->left);
//     if (tree->right)
//         free_tree(tree->right);
//     free_args(tree->argv);
//     free_redirs(tree->redirs);
//     free(tree);
// }

// /* Tokenise l'entrée, vérifie la syntaxe et retourne les tokens */
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
