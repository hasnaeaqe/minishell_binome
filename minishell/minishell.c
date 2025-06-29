/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:12:49 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/29 11:48:45 by haqajjef         ###   ########.fr       */
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
		//print_tokens(token);
		if (check_syntax_errors(token))
		{
			free_tokens(token);
			free(line);
			continue ;
		}
		expand_tokens(&token, env);
		if (handel_ambiguous(&token))
		{
			free_tokens(token);
			free(line);
			continue ;
		}
		flag=remove_quotes(&token);
		tree = parse_tree(&token,flag);
		// print_tree(tree, 0);
		handle_heredoc(tree, env);
		exec_tree(tree, &env);
		// puts("kk");
		free_tokens(token);
		free(line);
	}
	return (0);
}