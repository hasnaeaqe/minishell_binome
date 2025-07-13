/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:12:49 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/13 10:29:17 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static int	handle_line(char **line)
{
	*line = readline("minishell$ ");
	if (!*line)
	{
		write(1, "exit\n", 5);
		exit(exit_status(1, 1));
	}
	if (**line)
		add_history(*line);
	else
	{
		free(*line);
		return (0);
	}
	return (1);
}

static int	handle_signal(char *line)
{
	if (g_signal)
	{
		exit_status(1, 0);
		g_signal = 0;
		free(line);
		return (1);
	}
	return (0);
}

static void	process_line(char *line, t_env **env)
{
	t_token	*token;
	t_tree	*tree;
	int		flag;
	int		status;

	token = NULL;
	tokenisation(line, &token);
	if (check_syntax_errors(token))
	{
		free_tokens(token);
		free(line);
		return ;
	}
	max_herdoc(token);
	expand_tokens(&token, *env);
	handel_ambiguous(&token);
	splite_expand(&token);
	print_tokens(token);
	flag = flag_herdoc(&token);
	tree = parse_tree(&token, flag);
	print_tree(tree, 0);
	handle_heredoc(tree, *env);
	status = exec_tree(tree, env);
	setup_signals();
	exit_status(status, 0);
	free_tokens(token);
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = ft_env(envp);
	setup_signals();
	while (1)
	{
		if (!handle_line(&line))
			continue ;
		if (handle_signal(line))
			continue ;
		process_line(line, &env);
	}
	return (0);
}
