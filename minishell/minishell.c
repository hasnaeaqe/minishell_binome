/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:12:49 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/05 09:40:47 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token;
	t_tree	*tree;
	t_env *env;

	int flag;
	(void)argc;
	(void)argv;
	env = ft_env(envp);
	set_old_to_null(&env);
	// ft_printenv(env);
	while (1)
	{
		line = readline("minishell$ ");
		// built_pwd(env, 0);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		token = NULL;
		tokenisation(line, &token);
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
		print_tree(tree, 0);
		handle_heredoc(tree, env);
		exec_tree(tree, env);
		free_tokens(token);
		free(line);
	}
	return (0);
}
