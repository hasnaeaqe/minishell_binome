/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:08:19 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/13 20:12:39 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_expand(char *str)
{
    int i = 0;
    int j = 0;
    char *dest;
    while (str[i])
    {
        if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i]=='_')
            i++;
        else
            break;
    }
    dest = ft_malloc((i + 1) * sizeof(char));
    while (j < i)
    {
        dest[j] = str[j];
        j++;
    }
    dest[j]='\0';
    return (dest);
}
char *extract_value(char *dest, char **env)
{
    t_env *en;
    
    en = ft_env(env);
    while (en)
    {
        if (ft_strcmp(en->key, dest) == 0)
            return (en->value);
        en = en->next;
    }
    return (NULL);
}
char *rwina(char *value, char *expand_value, char *dest,int len)
{
    char *total_str;
    int i = 0;
    int j = 0;

    total_str = ft_malloc(len * sizeof(int));
    while (value[i])
    {
        if (value[i]=='$')
        {
            while (*expand_value)
                total_str[j++] = *expand_value++;
            i+=ft_strlen(dest) + 1;
        }
        else
        {
            total_str[j]=value[i];
            i++;
            j++;  
        }
    }
    total_str[j] = '\0';
    return (total_str);
}
void expand(t_token **token,char *str, char **env)
{
    char *dest;
    char *expand_value;
    t_token *tmp;
    int len;
    char *value;
    char *total_str;

    tmp = *token;
    value = (*token)->value;
    dest = find_expand(str);
    expand_value = extract_value(dest, env);
    //printf("%s\n",expand_value);
    len = ft_strlen((*token)->value) - ft_strlen(dest) + ft_strlen(expand_value);
    free((*token)->value);
    *token = ft_malloc(len * sizeof(t_token));
    total_str = rwina(value, expand_value, dest,len);
    (*token)->value = total_str;
    (*token)->next=tmp->next;
}
void	expand_tokens(t_token **token, char **env)
{
    t_token *tmp;
    char *str;
    int i;
    
    tmp = *token;
    while(tmp)
    {
        if (tmp->type == TOK_WORD)
        {
            str = tmp->value;
            i = 0;
            while (str[i])
            {
                if (str[i]=='\'')
                {
                    i++;
                    while(str[i] && str[i]!='\'')
                        i++;
                    if (str[i]=='\'')
                        i++;
                }
                else if (str[i] =='"')
                {
                    i++;
                    while (str[i] && str[i]!= '"')
                    {
                        if (str[i]=='$')
                        {
                            expand(&tmp,&str[++i], env);
                        }
                        i++;
                    }
                    if (str[i]=='"')
                        i++;
                }
                else
                {
                    if (str[i]=='$')
                        expand(&tmp,&str[++i], env);
                    i++;
                }
            }
            
        }
        printf("%s\n",tmp->value);
        tmp = tmp->next;
    }
}
