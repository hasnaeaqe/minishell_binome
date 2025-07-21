/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:03:36 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/21 15:22:24 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_fds(t_close_fds **head)
{
	if (!head || !*head)
		return ;
	while (*head)
	{
		close((*head)->fd);
		if ((*head)->kind == HER_DOC)
			unlink((*head)->filename);
		(*head) = (*head)->next;
	}
}

static t_close_fds	*create_fd(int fd, char *filename, int kind)
{
	t_close_fds	*new;

	new = ft_malloc(sizeof(t_close_fds));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->kind = kind;
	new->filename = filename;
	new->next = NULL;
	return (new);
}

static void	add_new_fd(t_close_fds **lst, t_close_fds *new)
{
	t_close_fds	*node;

	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	node = *lst;
	while (node && node->next)
		node = node->next;
	node->next = new;
}

int	open_fds(char *filename, int flag, int option, int kind)
{
	int					fd;
	static t_close_fds	*head;
	t_close_fds			*node;

	fd = -1;
	if (kind == OPEN || kind == HER_DOC)
	{
		if (option != 0)
			fd = open(filename, flag, option);
		else
			fd = open(filename, flag);
		node = create_fd(fd, filename, kind);
		add_new_fd(&head, node);
	}
	else
		close_fds(&head);
	return (fd);
}
