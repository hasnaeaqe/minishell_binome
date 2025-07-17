/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:06:39 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/17 18:25:03 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_pid(t_pid_list **list, pid_t pid)
{
    t_pid_list *new;
    new = ft_malloc(sizeof(t_pid_list));
    if (!new)
        return ;
    new->pid = pid;
    new->next = *list;
    *list = new;
}

void kill_all_pid(t_pid_list *list)
{
    t_pid_list *tmp;
    tmp = list;
    while (list)
    {
        tmp = list;
        kill(tmp->pid, SIGKILL);
        list = list->next;
    }
}

void free_all_pid(t_pid_list *list)
{
    t_pid_list *tmp;
    tmp = list;
    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}
