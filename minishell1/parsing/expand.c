/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:08:19 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/05 09:50:59 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
    if (!dest)
        return ("");
    if (ft_strcmp(dest,"?")==0)
        return (ft_itoa(exit_status(0, 1)));
    while (env)
    {
        if (ft_strcmp(env->key, dest) == 0)
            return (ft_strdup(env->value));
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
    int dest_len;
    
    dest_len = ft_strlen(dest);
    total_str = ft_malloc((len + 1) * sizeof(char)); //ila tra chi mochkil rah hna fin bdelt
    while (value[i])
    {
        printf("%c\n",value[i]);
        if (value[i]=='\'')
        {
            total_str[j++]=value[i++];
            while(value[i] && value[i]!='\'')
                total_str[j++]=value[i++];
            if (value[i]=='\'')
                total_str[j++]=value[i++];
        }
        else if (value[i]=='"')
        {
            total_str[j++]=value[i++];
            while(value[i] && value[i]!='"')
            {
                if (value[i]=='$' && value[i+1]  && ft_strncmp(&value[i+1],dest,dest_len)==0)
                {
                    k = 0;
                    if (expand_value)
                    {
                        while (expand_value[k])
                            total_str[j++] = expand_value[k++];
                    }
                    i+=dest_len+1;
                }
                else 
                    total_str[j++]=value[i++];    
            }
            if (value[i]=='"')
                total_str[j++]=value[i++];
        }
        else if (value[i]=='$' && value[i+1]  && ft_strncmp(&value[i+1],dest,dest_len)==0)
        {
            k = 0;
            if (expand_value)
            {
                while (expand_value[k])
                    total_str[j++] = expand_value[k++];
            }
            i+=dest_len+1;
        }
        else
            total_str[j++]=value[i++];
    }
    total_str[j] = '\0';
    return (total_str);
}
char *transform_to_gar(char *str)
{
    int i = 0;
    if (!str)
        return (NULL);
    while (str[i])
    {
        if (str[i]=='\'' || str[i]=='"')
            str[i]=str[i]*(-1);
        if (str[i]=='\t')
            str[i]=' ';
        i++;
    }
    return (str);
}
int count_expand(char *src, char *dest)
{
    int dest_len = ft_strlen(dest);
    int i = 0;
    int count=0;
    while (src[i])
    {
        if (src[i]=='\'')
        {
            i++;
            while(src[i] && src[i]!='\'')
                i++;
            if (src[i]=='\'')
                i++;
        }
        else if (src[i]=='"')
        {
            i++;
            while(src[i] && src[i]!='"')
            {
                if (src[i]=='$' && src[i+1]  && ft_strncmp(&src[i+1],dest,dest_len)==0)
                {
                    i+=ft_strlen(dest);
                    count++;
                }
                i++;
            }
            if (src[i]=='"')
                i++;
        }
        else if (src[i]=='$' && src[i+1]  && ft_strncmp(&src[i+1],dest,dest_len)==0)
        {
            count++;
            i++;
            i+=ft_strlen(dest);//tra xi haja rah hna 
        }
        else
            i++; 
    }
    return (count);
}
char *expand(char *src,char *str, t_env *env)
{
    char *dest;
    char *expand_value;
    int len;
    int count;

    dest = find_expand(str);
    expand_value = transform_to_gar(extract_value(dest, env));
    count = count_expand(src,dest);
    len = ft_strlen(src) - ft_strlen(dest)*count+ ft_strlen(expand_value)*count - count;
    // printf("count : %d\n",count);
    // printf("len :%d\n",len);
    printf("value : %s,str : %s  dest: %s , exapnd : %s , total: %s\n",src,str,dest,expand_value,rwina(src,dest,expand_value, len));
    return (ft_strdup(rwina(src,dest,expand_value, len)));
}
char *add_quotes(char *str)
{
    char *dest;
    int i = 0;

    dest = ft_malloc((ft_strlen(str)+3)*sizeof(char));
    while(*str && *str!='=' && *str!='+')
       dest[i++]=*str++;
    if (*str=='+')
        dest[i++]=*str++;
    if (*str=='=')
        dest[i++]=*str++;
    dest[i++]='"';
    while (*str)
        dest[i++]=*str++;
    dest[i++]='"';
    dest[i]='\0';
    return (dest);
}
// void check_export(t_token *token)
// {
//     t_token *tmp;
//     char *str;
//     int i ;
//     int check;

//     tmp=token;
//     while (tmp)
//     {
//         if (tmp->type==TOK_WORD)
//         {
//             check=0;
//             if (ft_strcmp(tmp->value,"export")==0 && tmp->next)
//             {
//                 str=ft_strdup(tmp->next->value);
//                 i = 0;
//                 while (str[i] && str[i]!='=' && str[i]!='+')
//                 {
//                     if (ft_isdigit(str[0]) || (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i]!='_'))
//                     {
//                         check = 1;
//                         break;
//                     }
//                     i++;
//                 }
//                 if (check == 0 && !ft_strchr(&str[i],'"') && !ft_strchr(&str[i],'\''))
//                     tmp->next->value=add_quotes(str);
//                 tmp=tmp->next;
//             }
//             tmp = tmp->next;
//         }
//     }
// }
void check_export(t_token *token)
{
    char *str;
    int i;
    int check;
    if (ft_strcmp(token->value,"export")==0 && token->next)
    {
        check=0;
        str=ft_strdup(token->next->value);
        i = 0;
        while (str[i] && str[i]!='=')
        {
            if (str[i]=='+' && str[i+1]=='=')
                break;
            if (ft_isdigit(str[0]) || (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i]!='_') )
            {
                check = 1;
                break;
            }
            i++;
        }
        if (check == 0 && !ft_strchr(&str[i],'"') && !ft_strchr(&str[i],'\''))
            token->next->value=add_quotes(str);
    }
}
void	expand_tokens(t_token **token, t_env *env)
{
    t_token *tmp;
    t_token *prev;
    char *str;
    int i;
    
    tmp = *token;
    prev = *token;
    check_export(tmp);
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
                    if (str[i]=='\'' && i!=0)
                        i++;
                }
                else if (str[i] =='"')
                {
                    i++;
                    while (str[i] && str[i]!= '"')
                    {
                        if (str[i]=='$' && str[i+1] && str[i+1]=='"')
                            i+=2;
                        else if (str[i]=='$' && str[i+1] )
                        {
                            str=expand(str,&str[i], env);
                            i = 0;
                            break; 
                        }
                        else
                            i++;
                    }
                    if (str[i]=='"' && i!=0)
                        i++;   
                }
                else if (str[i]=='$' && str[i+1])
                {
                    str=expand(str,&str[i], env);
                    i = 0;
                }
                else
                {
                    i++;
                }
            }
            free(tmp->value);//ila tra chi mochkil rah hna
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
    char *str;
    char quote;
    int i = 0;
    tmp = *token;
    while (tmp)
    {
        if (tmp->type==TOK_REDIR_APPEND || tmp->type==TOK_REDIR_INPUT || tmp->type==TOK_REDIR_OUTPUT)
        {
            i = 0;
            str = tmp->next->value;
            if (str[0]=='\0')
            {
                ft_putstr_fd("minishell: ambiguous redirect \n", 2);
                exit_status(1, 0);
                return (1);
            }
            while (str[i])
            {
                
                if (str[i]=='"' || str[i]=='\'')
                {
                    quote=str[i++];
                    while(str[i] && str[i]!=quote)
                        i++;
                    if (str[i]==quote)
                        i++;
                }
                else if (str[i]==' ')
                {
                    ft_putstr_fd("minishell: ambiguous redirect \n", 2);
                    exit_status(1, 0);
                    return (1);
                }
                else
                    i++;
            }
        }
        tmp=tmp->next;
    }
    return (0);
}
void tkherbi9a(t_token **token)
{
    t_token *tmp;
    t_token *add;
    t_token *prev=NULL;
    t_token *neext=NULL;
    char quote;
    char *dest;
    char *str;
    int i;
    int start;

    tmp=*token;
    while (tmp)
    {
        if (tmp->type==TOK_WORD)
        {
            if(ft_strchr(tmp->value,' '))
            {
                neext=tmp->next;
                str=ft_strdup(tmp->value);
                i=0;
                start = i;
                // puts(neext->value);
                while (str[i])
                {
                    if (str[i]=='\'' || str[i]=='"')
                    {
                        quote = str[i++];
                        while (str[i] && str[i]!=quote)
                            i++;
                        if (str[i]==quote)
                            i++;
                    }
                    else if (str[i]==' ' || str[i]=='\0')
                    {
                        dest=ft_substr(str,start,i - start);
                        add = new_token(TOK_WORD,dest);
                        if (!prev)
                        {
                            free( tmp->value);
                            tmp->value=ft_strdup(dest);
                            prev=tmp;
                        }
                        else
                        {
                            prev->next=add;
                            prev=prev->next;
                            tmp=prev;////////////ila tra chi mochkil hna
                        }
                        if (str[i])
                            start = ++i;
                    }
                    else
                        i++;
                }
                //  printf("%c\n",str[i]);
                dest=ft_substr(str,start,i - start);
                add = new_token(TOK_WORD,dest);
                // printf("%d\n",start);
                if (!prev)
                {
                    free( tmp->value);
                    tmp->value=ft_strdup(dest);
                    prev=tmp;
                }
                else
                {
                    prev->next=add;
                    prev=prev->next;
                    prev->next=neext;
                    tmp=prev;//////////ila tra chi mochkil hna 
                }
                if (neext)
                    prev->next=neext;
            }
            else
                prev=tmp;
        }
        else
            prev=tmp;
        tmp=tmp->next;
    }
}
// char *handel_delemiter_expand(char *delimiter)
// {
    
// }