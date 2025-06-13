/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:37:08 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/13 21:52:46 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_functions(char *str, char **env)
{
    int i=0;
    char *resutl_str;
    while(str[i])
    {
        if (str[i]=='\'')
        {
            i++;
            while(str[i] && str[i]!='\'')
                i++;
            if (str[i]=='\'')
                i++;
            resutl_str=ft_my_strlcat(resutl_str,str,i); //segfault f had fonction 
            //printf("%s\n",resutl_str);
        }
        else if (str[i] =='"')
        {
            i++;
            while (str[i] && str[i]!= '"')
            {
                printf("%s",*env);
                // if (str[i]=='$')
                // {
                //     expand(&tmp,&str[++i], env);
                // }
                i++;
            }
            if (str[i]=='"')
                i++;
        }
        else
        {
            // if (str[i]=='$')
            //     expand(&tmp,&str[++i], env);
            i++;
        }
           
    }
    return (NULL);
}
