/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_tree_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:07:26 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/12 20:38:35 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redir_node(t_redir_node **redir, t_redir_type kind,
	char *filename, int flag, int ambiguous)
{
	t_redir_node	*new;
	t_redir_node	*tmp;

	new = new_redir(kind, filename, flag, ambiguous);
	if (!new)
		return ;
	if (!(*redir))
		*redir = new;
	else
	{
		tmp = *redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static void	handle_redirection_token(t_token *tmp, t_token **token,
	t_redir_node **redir, int flag)
{
	if (tmp->next && tmp->type == TOK_REDIR_APPEND)
		redir_node(redir, REDIR_APPEND, tmp->next->value, flag, tmp->ambig);
	else if (tmp->next && tmp->type == TOK_REDIR_HEREDOC)
		redir_node(redir, REDIR_HEREDOC, tmp->next->value, flag, tmp->ambig);
	else if (tmp->next && tmp->type == TOK_REDIR_INPUT)
		redir_node(redir, REDIR_INPUT, tmp->next->value, flag, tmp->ambig);
	else if (tmp->next && tmp->type == TOK_REDIR_OUTPUT)
		redir_node(redir, REDIR_OUTPUT, tmp->next->value, flag, tmp->ambig);
	*token = tmp->next;
}

static int	parse_loop_tokens(t_token **token, char ***argv,
	t_redir_node **redir, int flag)
{
	t_token	*tmp;
	char	*str;
	int		i;

	i = 0;
	while (*token && (*token)->type != TOK_PIPE)
	{
		tmp = *token;
		str = tmp->value;
		if ((tmp)->type == TOK_WORD && str[0] != '\0')
			(*argv)[i++] = trasform_garbeg(rm_quotes(str));
		else if (is_redi_operator(tmp->type))
			handle_redirection_token(tmp, token, redir, flag);
		*token = (*token)->next;
	}
	return (i);
}

static size_t	count_args(t_token **token)
{
	size_t		i;
	t_token		*tmp;
	char		*str;

	i = 0;
	tmp = *token;
	while (tmp && tmp->type != TOK_PIPE)
	{
		str = tmp->value;
		if (tmp->type == TOK_WORD && str[0] != '\0')
			i++;
		else if (is_redi_operator(tmp->type))
		{
			tmp = tmp->next;
			if (!tmp)
				break ;
		}
		tmp = tmp->next;
	}
	return (i);
}

t_tree	*parse_commande(t_token **token, int flag)
{
	t_redir_node	*redir;
	char			**argv;
	size_t			i;

	i = count_args(token);
	if (i < 0)
		return (NULL);
	argv = ft_malloc(sizeof(char *) * (i + 1));
	redir = NULL;
	i = parse_loop_tokens(token, &argv, &redir, flag);
	argv[i] = NULL;
	return (new_tree(NODE_COMMAND, argv, redir));
}
