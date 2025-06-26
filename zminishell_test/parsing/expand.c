/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:08:19 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/26 15:26:12 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_expand(char *str)
{
    int i = 1;
    int j = 0;
    char *dest;
    
    if (!str || str[0] != '$' )
        return (ft_strdup(""));
    if (str[1]=='?')
        return (ft_strdup("?"));
    if (ft_isdigit(str[i]))
    {
        dest = ft_malloc(2 * sizeof(char));
        dest[j++]=str[i];
        dest[j]='\0';
        return (dest);
    }
    while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i]=='_'))
        i++;
    dest = ft_malloc((i + 1) * sizeof(char));
    if (j==i-1)
       dest[j++]=str[i]; 
    else
    {
        while (j < i - 1)
        {
            dest[j] = str[j+1]; 
            j++;
        }
    }
    dest[j] = '\0';
    return (dest);
}
char *extract_value(char *dest, t_env *env)
{

    if (ft_strcmp(dest,"?")==0)
        return (dest);
    while (env)
    {
        if (ft_strcmp(env->key, dest) == 0)
            return (env->value);
        env = env->next;
    }
    return ("");
}
char *rwina(char *value,char *dest,char *expand_value, int len)
{
    char *total_str;
    int k;
    int i = 0;
    int j = 0;
    int dest_len = ft_strlen(dest);

    total_str = ft_malloc((len + 1) * sizeof(char)); //ila tra chi mochkil rah hna fin bdelt
    while (value[i])
    {
        if (value[i]=='$' && ft_strncmp(&value[i+1],dest,dest_len)==0)
        {
            k = 0;
            while (expand_value[k])
                total_str[j++] = expand_value[k++];
            i+=dest_len+1;
        }
        else
            total_str[j++]=value[i++]; 
    }
    total_str[j] = '\0';
    return (total_str);
}
char *expand(char *src,char *str, t_env *env)
{
    char *dest;
    char *expand_value;
    int len;

    dest = find_expand(str);
    expand_value = extract_value(dest, env);
    len = ft_strlen(src) - ft_strlen(dest) + ft_strlen(expand_value);
    // printf("value : %s,str : %s  dest: %s , exapnd : %s , TOTAL : %s\n",src,str,dest,expand_value,rwina(src,dest,expand_value, len));
    return (rwina(src,dest,expand_value, len));
}
int petit_test(char *str,int *k)
{
    int i=0;
    while (str[i] && str[i]=='$')
    {
        i++;
        (*k)++;
    }
    (*k)--;
    return (i);
}
void	expand_tokens(t_token **token, t_env *env)
{
    t_token *tmp;
    t_token *prev;
    char *str;
    int i;
    
    tmp = *token;
    prev = *token; 
    while(tmp)
    {
        if (tmp->type == TOK_WORD && prev->type != TOK_REDIR_HEREDOC)
        {
            str = ft_strdup(tmp->value);
            i = 0;
            while (str[i])
            {
                if (str[i]=='\'')
                {
                    i++;
                    while(str[i] && str[i]!='\'')
                        i++;
                }
                else if (str[i] =='"')
                {
                    i++;
                    while (str[i] && str[i]!= '"')
                    {
                        if (str[i]=='$' && str[i+1])
                        {
                            str=expand(str,&str[i], env);
                            i = 0;
                            break; 
                        }
                        else
                            i++;
                    }
                }
                else if (str[i]=='$' && str[i+1])
                {
                    str=expand(str,&str[i], env);   
                    i = 0;
                }
                else
                    i++;
            }
            tmp->value = str;
        }
        // printf("%s\n",tmp->value);
        prev=tmp;
        tmp = tmp->next;
    }
}
char *expand_heredoc(char *line, t_env *env)
{
    int i = 0;

    while (line[i])
    {
        if (line[i]=='$' && line[i+1])
            line=expand(line,&line[i], env);
        else
            i++;
    }
    return (line);
}
int handel_ambiguous(t_token **token)
{
    t_token *tmp;

    tmp = *token;
    while (tmp)
    {
        if (tmp->type==TOK_REDIR_APPEND || tmp->type==TOK_REDIR_INPUT || tmp->type==TOK_REDIR_OUTPUT)
        {
            if (ft_count(tmp->next->value, ' ') != 1)
            {
                ft_putstr_fd("minishell: ambiguous redirect \n", 2);
                return (1);
            }
        }
        tmp=tmp->next;
    }
    return (0);
}