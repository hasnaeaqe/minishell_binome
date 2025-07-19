/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:12:49 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/19 20:32:34 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static int	handle_line(char **line1)
{
	if (!*line1)
	{
		write(1, "exit\n", 5);
		exit(exit_status(0, 1));
	}
	if (**line1)
		add_history(*line1);
	else
	{
		ft_free(*line1, 1);
		return (0);
	}
	return (1);
}

void	handel_signal(void)
{
	if (g_signal)
	{
		exit_status(1, 0);
		g_signal = 0;
	}
}

static int	process_line(char *line, t_env **env)
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
		return (free_tokens(token), ft_free(line, 1), 1);
	expand_tokens(&token, *env);
	handel_ambiguous(&token);
	splite_expand(&token);
	flag = flag_herdoc(&token);
	tree = parse_tree(&token, flag);
	if (handle_heredoc(tree, *env, &stop) == 2)
		return (free_tokens(token), ft_free(line, 1), exit_status(1, 0), 1);
	status = exec_tree(tree, env, 0);
	setup_signals();
	(exit_status(status, 0), free_tokens(token));
	return (ft_free(line, 1), 0);
}

void	check_args(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("invalide args !\n", 2);
		exit(1);
	}
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("minishell: not interactive input\n", 2);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*line1;
	t_env	*env;

	(void)argv;
	env = ft_env(envp);
	if (!env)
		return (1);
	setup_signals();
	check_args(argc);
	while (1)
	{
		line = readline("minishell$ ");
		line1 = ft_strdup(line);
		if (!handle_line(&line1))
			continue ;
		handel_signal();
		if (process_line(line1, &env))
			continue ;
		free(line);
	}
	ft_free(line1, 1);
	free(line);
	return (0);
}
