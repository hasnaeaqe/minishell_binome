/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:02:12 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/01 16:25:47 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char *rm_qts(char *src, int len)
{
    char *dest;
    char quote;
    int i=0;
    int j=0;

    dest = ft_malloc((len + 1) * sizeof(char));
    while (src[i])
    {
        if (src[i]=='\'' || src[i]=='"')
        {
            quote = src[i++];
            while (src[i] && src[i]!=quote)
                dest[j++]=src[i++];
            if (src[i]==quote)
                i++;
        }
        else
            dest[j++]=src[i++];
    }
    dest[j]='\0';
    return (dest);
}

char *trasform_garbeg(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (!ft_isascii(str[i]))
            str[i]=str[i]*(-1);
        i++;
    }
    return (str);
}
int  remove_quotes(t_token **token)
{
    t_token *tmp;
    char *src;
    char quote;
    int len;
    int i;
    int flag=0;
    tmp = *token;
    
    while (tmp)
    {
        if (tmp->type==TOK_REDIR_HEREDOC)
        {
            if (ft_strchr(tmp->next->value,'\'') || ft_strchr(tmp->next->value,'"'))
                flag=1;  
        }
        if (tmp->type==TOK_WORD)
        {
            src = ft_strdup(tmp->value);
            i = 0;
            len = 0;
            while (src[i])
            {
                if (src[i]=='\'' || src[i]=='"')
                {
                    quote = src[i++];
                    while (src[i] && src[i]!=quote)
                    {
                       len++; 
                       i++;
                    }
                    if (src[i]==quote)
                        i++;
                }
                else
                {
                    len++;
                    i++;
                }
            }
            tmp->value=trasform_garbeg(rm_qts(src,len));
        }
        tmp = tmp->next;
    }
    return (flag);
}
