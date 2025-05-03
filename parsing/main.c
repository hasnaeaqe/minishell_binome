/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:32:06 by cbayousf          #+#    #+#             */
/*   Updated: 2025/05/03 20:21:59 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *type_token(t_tok_type type)
{
    if (type == TOK_WORD)
        return "WORD";
    else if (type == TOK_PIPE)
        return "PIPE";
    else if (type == TOK_REDIR_IN)
        return "REDIR_IN";
    else if (type == TOK_REDIR_OUT)
        return "REDIR_OUT";
    else if (type == TOK_REDIR_APPEND)
        return "REDIR_APPEND";
    else if (type == TOK_REDIR_HEREDOC)
        return "REDIR_HEREDOC";
    else
        return "UNKNOWN";
}
void print_tokens(t_token *token)
{
    t_token *tmp;
    tmp=token;
    while(tmp)
    {
        printf("type : %s | value : %s\n",type_token(tmp->type),tmp->value);
        tmp=tmp->next;
    }
}
void free_tokens(t_token *token)
{
    t_token *tmp;
    while(token)
    {
        tmp=token;
        token=token->next;
        free(tmp->value);
        free(tmp);
    }
}
t_token *new_token(t_tok_type type,char *value)
{
    t_token *new;
    
    new  = ft_malloc(sizeof(t_token));
    new->type = type;
    new->value = ft_strdup(value);
    if (!new)
    {
        free(new);
        return NULL;
    }
    new->next = NULL;
    return (new);
}
void add_token(t_token **token, t_tok_type type, char *value)
{
    t_token *tmp;
    t_token *new;
    new = new_token(type, value);
    if (!token || !new)
        return ;
    if (!*token)
        *token=new;
    else
    {
        tmp=*token;
        while(tmp->next)
            tmp=tmp->next;
        tmp->next=new;
    }
}
void tokenisation(char *str,t_token **token)
{
    int start;
    char *word_quote;
    char quote;
    int i;
    i = 0;
    
   
    while(str[i])
    {
        while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
            i++;
        if(str[i]=='|')
        {
            add_token(token,TOK_PIPE,"|");
            i++;
        }
        else if (str[i]=='<')
        {
            if (str[i+1]=='<')
            {
                add_token(token,TOK_REDIR_HEREDOC,"<<");
                i+=2;
            }
            else
            {
                add_token(token,TOK_REDIR_IN,"<");
                i++;
            }
        }
        else if (str[i]=='>')
        {
            if (str[i+1]=='>')
            {
                add_token(token,TOK_REDIR_APPEND,">>");
                i+=2;
            }
            else
            {
                add_token(token,TOK_REDIR_OUT,">");
                i++;
            }
        }
        else if (str[i]== '\'' || str[i]=='"')
        {
            quote=str[i];
            start = i++;
            while(str[i])
            {
                if(str[i]!=quote)
                    i++;
                else{
                    while(str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '<' && str[i]!='>')
                        i++;
                    break;
                }
            }
            if (i > start)
            {
                word_quote=ft_strndup(&str[start],i-start);
                add_token(token,TOK_WORD,word_quote);
            }
            if (str[i])
                i++;
        }
        else
        {
            start = i;
            while(str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '<' && str[i]!='>')
                i++;
            if (i> start)
            {
                word_quote=ft_strndup(&str[start],i-start);
                add_token(token,TOK_WORD,word_quote);
            }
        }
    }
}
// void f()
// {
//     system("leaks a.out");
// }
int main(void)
{
    char *line;
    t_token *token;
    //atexit(f);
    while (1)
    {
        line = readline("minishell$ ");
        if (!line) 
            break;
        if (*line)
            add_history(line);
        token=NULL;
        tokenisation(line,&token);
        print_tokens(token);
        if(check_syntax_errors(token)!=0)
        {
            free_tokens(token);
            free(line);
            return (1);
        }
        free_tokens(token);
        free(line);
    }
    return 0;
}