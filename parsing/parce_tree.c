/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:44:22 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/18 15:11:17 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	finde_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOK_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_redir_node	*new_redir(t_redir_type kind, char *filename)
{
	t_redir_node	*new;

	new = ft_malloc(sizeof(t_redir_node));
	new->kind = kind;
	new->filename = ft_strdup(filename);
	new->next = NULL;
	return (new);
}

void	redir_node(t_redir_node **redir, t_redir_type kind, char *filename)
{
	t_redir_node	*new;
	t_redir_node	*tmp;

	new = new_redir(kind, filename);
	if (!redir || !new)
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

t_tree	*new_tree(t_node_type kind, char **argv, t_redir_node *redirs)
{
	t_tree	*new;

	new = ft_malloc(sizeof(t_tree));
	new->kind = kind;
	new->argv = argv;
	new->redirs = redirs;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_tree	*parse_commande(t_token **token)
{
	t_node_type		kind;
	t_redir_node	*redir;
	t_token			*tmp;
	char			**argv;
	int				i;

	i = 0;
	redir = NULL;
	argv = NULL;
	tmp = *token;
	while (tmp && tmp->type != TOK_PIPE)
	{
		if (tmp->type == TOK_WORD)
			i++;
		else 
			tmp = tmp->next;
		tmp = tmp->next;
	}
	argv = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (*token && (*token)->type != TOK_PIPE)
	{
		tmp = *token;
		if ((tmp)->type == TOK_WORD)
		{
			argv[i++] = ft_strdup(tmp->value);
		}
		else
		{
			if (tmp->next && tmp->type == TOK_REDIR_APPEND)
				redir_node(&redir, REDIR_APPEND, tmp->next->value);
			else if (tmp->next && tmp->type == TOK_REDIR_HEREDOC)
				redir_node(&redir, REDIR_HEREDOC, tmp->next->value);
			else if (tmp->next && tmp->type == TOK_REDIR_INPUT)
				redir_node(&redir, REDIR_INPUT, tmp->next->value);
			else if (tmp->next && tmp->type == TOK_REDIR_OUTPUT)
				redir_node(&redir, REDIR_OUTPUT, tmp->next->value);
			*token = tmp->next;
		}
		*token = (*token)->next;
	}
	argv[i] = NULL;
	kind = NODE_COMMAND;
	return (new_tree(kind, argv, redir));
}

t_tree	*create_tree(t_tree *left, t_tree *right)
{
	t_tree	*new;

	new = new_tree(NODE_PIPE, NULL, NULL);
	new->left = left;
	new->right = right;
	return (new);
}

t_tree	*parse_pipe(t_token **token)
{
	t_tree	*left;
	t_tree	*right;

	left = parse_commande(token);
	if (*token && (*token)->type == TOK_PIPE)
	{
		*token = (*token)->next;
		right = parse_pipe(token);
		return (create_tree(left, right));
	}
	return (left);
}

t_tree	*parse_tree(t_token **token)
{
	if (finde_pipe(*token))
	{
		return (parse_pipe(token));
	}
	else
	{
		return (parse_commande(token));
	}
}
