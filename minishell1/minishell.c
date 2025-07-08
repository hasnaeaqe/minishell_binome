/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:12:49 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/08 16:17:52 by cbayousf         ###   ########.fr       */
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
		// atexit(f);
	env = ft_env(envp);
	// update_value(env, "OLDPWD", NULL);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		else
			continue ;
		token = NULL;
		tokenisation(line, &token);
		if (check_syntax_errors(token))
		{
			free_tokens(token);
			free(line);
			continue ;
		}
		expand_tokens(&token, env);
		handel_ambiguous(&token);
		// print_tokens(token);
		// if (handel_ambiguous(&token))
		// {
		// 	free(line);
		// 	free_tokens(token);
		// 	continue ;
		// }
		// print_tokens(token);
		splite_expand(&token);
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
