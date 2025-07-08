/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_tree_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:44:22 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/08 12:00:40 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static t_tree	*create_tree(t_tree *left, t_tree *right)
{
	t_tree	*new;

	new = new_tree(NODE_PIPE, NULL, NULL);
	new->left = left;
	new->right = right;
	return (new);
}

static t_tree	*parse_pipe(t_token **token, int flag)
{
	t_tree	*left;
	t_tree	*right;

	left = parse_commande(token, flag);
	// if (!left)
	// 	return (NULL);
	if (*token && (*token)->type == TOK_PIPE)
	{
		*token = (*token)->next;
		right = parse_pipe(token, flag);
		return (create_tree(left, right));
	}
	return (left);
}

static int	finde_pipe(t_token *token)
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

t_tree	*parse_tree(t_token **token, int flag)
{
	// if (!token || !*token)
	// 	return (NULL);
	if (finde_pipe(*token))
		return (parse_pipe(token, flag));
	else
		return (parse_commande(token, flag));
}
