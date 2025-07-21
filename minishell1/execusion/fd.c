/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:03:36 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/20 10:25:42 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static    void    close_fds(t_close_fds **head)
{
    if (!head || !*head)
        return ;
    while (*head)
    {
        close((*head)->fd);
        if ((*head)->Kind == HER_DOC)
            unlink((*head)->filename);
        (*head) = (*head)->next;
    }
}

static t_close_fds    *create_fd(int fd, char *filename, int Kind)
{
    t_close_fds    *new;

    new = ft_malloc(sizeof(t_close_fds));
    if (!new)
        return (NULL);
    new->fd = fd;
    new->Kind = Kind;
    new->filename = filename;
    new->next = NULL;
    return (new);
}

static    void    add_new_fd(t_close_fds **lst, t_close_fds *new)
{
    t_close_fds    *node;

    if (!lst)
        return ;
    if (!(*lst))
    {
        *lst = new;
        return ;
    }
    node = (*lst);
    while (node && node->next)
        node = node->next;
    node->next = new;
}

int    open_fds(char *filename, int flag, int option, int Kind)
{
    int                fd;
    static t_close_fds    *head;
    t_close_fds            *node;

    fd = -1;
    if (Kind == OPEN || Kind == HER_DOC)
    {
        if (option != 0)
            fd = open(filename, flag, option);
        else
            fd = open(filename, flag);
        node = create_fd(fd, filename, Kind);
        add_new_fd(&head, node);
    }
    else
        close_fds(&head);
    return (fd);
}