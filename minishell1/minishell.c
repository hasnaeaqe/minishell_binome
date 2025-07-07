/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:12:49 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/07 20:15:47 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void f(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	printf("Bienvenue dans une nouvelle instance de minishell 🐚\n");
	char	*line;
	t_token	*token;
	t_tree	*tree;
	t_env *env;
	// atexit(f);
	int flag;
	(void)argc;
	(void)argv;
	env = ft_env(envp);
	// update_value(env, "OLDPWD", NULL);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		token = NULL;
		tokenisation(line, &token);
		// print_tokens(token);
		if (check_syntax_errors(token))
		{
			free_tokens(token);
			free(line);
			continue ;
		}
		expand_tokens(&token, env);
		// if (handel_ambiguous(&token))
		// {
		// 	free(line);
		// 	free_tokens(token);
		// 	continue ;
		// }
		// print_tokens(token);
		tkherbi9a(&token);
		// print_tokens(token);
		flag=remove_quotes(&token);
		// print_tokens(token);
		tree = parse_tree(&token,flag);
		// print_tree(tree, 0);
		handle_heredoc(tree, env);
		int status  = exec_tree(tree, &env);
		// printf("status == %d\n", status);
		exit_status(status , 0);
		free_tokens(token);
		free(line);
	}
	return (0);
}
