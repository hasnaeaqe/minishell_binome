/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:49:09 by haqajjef          #+#    #+#             */
/*   Updated: 2025/07/04 11:49:24 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin_3(char *s1, char *s2, char *s3)
{
    char *tmp;
    char *res;

    tmp = ft_strjoin(s1, s2);
    res = ft_strjoin(tmp, s3);
    free(tmp);
    return res;
}

char **to_array(t_env *env, int size)
{
    char **array;
    t_env *tmp;
    int i;

    array = ft_malloc(sizeof(char *) * (size + 1));
    tmp = env;
    i = 0;
    while (i < size && tmp)
    {
        array[i] = ft_strjoin_3(tmp->key, "=", tmp->value);
        tmp = tmp->next;
        i++;
    }
    array[i] = NULL;
    return (array);
}
