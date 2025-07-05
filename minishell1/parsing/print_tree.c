/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:11:41 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/30 17:41:03 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tree(t_tree *tree, int depth)
{
	if (!tree)
		return ;

	for (int i = 0; i < depth; i++)
		printf("  ");
	if (tree->kind == NODE_COMMAND)
	{
		printf("NODE_COMMAND\n");
		for (int i = 0; tree->argv && tree->argv[i]; i++)
		{
			for (int j = 0; j < depth + 1; j++)
				printf("  ");
			printf("ARGV[%d] = %s\n", i, tree->argv[i]);
		}
		t_redir_node *redir = tree->redirs;
		while (redir)
		{
			const char *type_str = "";
			switch (redir->kind)
			{
				case REDIR_INPUT:     type_str = "REDIR_INPUT"; break;
				case REDIR_OUTPUT:    type_str = "REDIR_OUTPUT"; break;
				case REDIR_APPEND:    type_str = "REDIR_APPEND"; break;
				case REDIR_HEREDOC:   type_str = "REDIR_HEREDOC"; break;
				default:              type_str = "UNKNOWN_REDIR"; break;
			}

			for (int j = 0; j < depth + 1; j++)
				printf("  ");
			printf("REDIR %s -> %s flag :%d \n", type_str, redir->filename, redir->flag);
			redir = redir->next;
		}
	}
	else if (tree->kind == NODE_PIPE)
	{
		printf("NODE_PIPE\n");
	}

	if (tree->left)
	{
		for (int i = 0; i < depth; i++)
			printf("  ");
		printf("LEFT:\n");
		print_tree(tree->left, depth + 1);
	}

	if (tree->right)
	{
		for (int i = 0; i < depth; i++)
			printf("  ");
		printf("RIGHT:\n");
		print_tree(tree->right, depth + 1);
	}
}