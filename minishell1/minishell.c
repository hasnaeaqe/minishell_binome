/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:12:49 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/16 15:25:10 by haqajjef         ###   ########.fr       */
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
		exit(exit_status(0, 1));
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

static void	process_line(char *line, t_env **env)
{
	t_token	*token;
	t_tree	*tree;
	int		flag;
	int		status;
	int		stop;

	stop = 0;
	token = NULL;
	tokenisation(line, &token);
	if (check_syntax_errors(token))
	{
		free_tokens(token);
		free(line);
		return ;
	}
	(max_herdoc(token),expand_tokens(&token, *env));
	handel_ambiguous(&token);
	splite_expand(&token);
	flag = flag_herdoc(&token);
	tree = parse_tree(&token, flag);
	handle_heredoc(tree, *env, &stop);
	status = exec_tree(tree, env, 0);
	setup_signals();
	(exit_status(status, 0),free_tokens(token));
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
	if (argc != 1)
	{
		ft_putstr_fd("invalide args !", 2);
		return (1);
	}
	while (1)
	{
		if (!handle_line(&line))
			continue ;
		if (g_signal)
		{
			exit_status(1, 0);
			g_signal = 0;
		}
		process_line(line, &env);
	}
	return (0);
}
