/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:19:41 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/08 18:31:31 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"
#include <string.h>

void add_to_env(t_env **env, char *key_to_add)
{
    t_env *tmp;
    t_env *new_node;

    new_node = create_node(key_to_add, "");
    tmp = *env;
    if(!tmp)
    {
        *env = new_node;
        return;
    }
    while(tmp -> next)
    {
        tmp = tmp->next;
    }
    tmp->next = new_node;
}
void ft_export(char **argv, t_env **env)
{
    int i;
    i = 0;
    while(argv[i])
    {
        add_to_env(env, argv[i]);
        printf("heey\n");
        i++;
    }
}


void    ft_lstadd_back(t_env **lst, t_env *new)
{
    t_env    *tmp;

    if (lst == NULL || new == NULL)
        return ;
    if (*lst == NULL)
    {
        *lst = new;
        new->next = NULL;
        return ;
    }
    else
    {
        tmp = *lst;
        while (tmp -> next)
        {
            tmp = tmp-> next;
        }
        tmp -> next = new;
    }
}
int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("entrer autre argument");
        return (1);
    }
    printf("Avant export :\n");
    t_env *head =  NULL;
    int i = 1;
    while(argv[i])
    {
        char *key = ext_key(argv[i]);
        char *val = ext_val(argv[i]);
        t_env *new = create_node(key, val);
        ft_lstadd_back(&head, new);
        i++;
    }
    ft_printenv(head);

    printf("\nAprès export :\n");
    char *to_export[] = {"VIM=", NULL};
    ft_export(to_export, &head);

    ft_printenv(head);

    return 0;
}
