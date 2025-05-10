/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remplir_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:46:21 by cbayousf          #+#    #+#             */
/*   Updated: 2025/05/10 20:25:04 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_pipe(t_token *token)
{
    t_token *tmp;
    
    tmp = token;
    while (tmp)
    {
        if(tmp->type == TOK_PIPE)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

t_tree *new_tree(t_node_type kind, char **argv, t_redir_node *redirs)
{
    t_tree *new;
    
    new = ft_malloc(sizeof(t_tree));
    new->kind = kind;
    new->argv = argv;
    new->redirs = redirs;
    new->left = NULL;
    new->right = NULL;
    return (new);
}

t_redir_node *new_redir_node(t_redir_type kind, char *filename)
{
    t_redir_node *new;
    
    new  = ft_malloc(sizeof(t_redir_node));
    new->kind = kind;
    new->filename = ft_strdup(filename);
    new->next = NULL;
    return (new);
}
void add_redir_node(t_redir_node **redir, t_redir_type kind, char *filename)
{
    t_redir_node *tmp;
    t_redir_node *new;
    new = new_redir_node(kind, filename);
    if (!redir || !new)
        return ;
    if (!*redir)
        *redir=new;
    else
    {
        tmp=*redir;
        while(tmp->next)
            tmp=tmp->next;
        tmp->next=new;
    }
}
t_tree *parse_commande(t_token **token)
{
    t_node_type kind;
    t_token *tmp;
    t_tree *tree;
    char **argv=NULL;
    int i;
    t_redir_node *redirs=NULL;

    i = 0;
    tmp = *token;
    while (tmp && tmp->type != TOK_PIPE)
    {
        if (tmp->type==TOK_WORD)
            i++;
        tmp=tmp->next;
    }
    argv=ft_malloc(sizeof(char *)*(i + 1));
    i=0;
    while (*token && (*token)->type != TOK_PIPE)
    {
        tmp=*token;
        if (tmp->type == TOK_WORD)
           argv[i++]=ft_strdup(tmp->value);
        else
        {
            if (tmp->next)
            {
                if (tmp->type == TOK_REDIR_APPEND)
                    add_redir_node(&redirs,REDIR_APPEND,tmp->next->value);
                else if (tmp->type == TOK_REDIR_HEREDOC)
                    add_redir_node(&redirs,REDIR_HEREDOC,tmp->next->value);
                else if (tmp->type == TOK_REDIR_INPUT)
                    add_redir_node(&redirs,REDIR_INPUT,tmp->next->value);
                else if (tmp->type == TOK_REDIR_OUTPUT)
                    add_redir_node(&redirs,REDIR_OUTPUT,tmp->next->value);
                *token = tmp->next;
            }
        }
        *token = (*token)->next;
    }
    kind=NODE_COMMAND;
    argv[i]=NULL;
    return (new_tree(kind,argv,redirs));
}
t_tree *add_tree(t_tree *left, t_tree *right)
{
    t_tree *new;

    new = new_tree(NODE_PIPE,NULL,NULL);
    new->left=left;
    new->right=right;
    return new;
}
t_tree *parse_pipe(t_token **token)
{
    t_tree *left;
    t_tree *right;
    t_token *tmp;
    
    left=parse_commande(token);
    tmp = *token;
    if (tmp && tmp->type == TOK_PIPE)
    {
        *token=tmp->next;
        right = parse_pipe(token);
        return add_tree(left,right);
    }
    return left;
}
t_tree *remplir_tree(t_token **token)
{
    if (find_pipe(*token))
        return (parse_pipe(token));
    else
        return (parse_commande(token));
}

