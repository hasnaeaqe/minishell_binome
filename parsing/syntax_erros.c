/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_erros.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:22:59 by cbayousf          #+#    #+#             */
/*   Updated: 2025/05/03 20:25:22 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_operator(t_tok_type type)
{
    return (type == TOK_PIPE ||
            type == TOK_REDIR_IN ||
            type == TOK_REDIR_OUT ||
            type == TOK_REDIR_APPEND ||
            type == TOK_REDIR_HEREDOC);
}
int check_syntax_errors(t_token *token)
{
    
}