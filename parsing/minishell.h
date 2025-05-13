/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:33:22 by cbayousf          #+#    #+#             */
/*   Updated: 2025/05/12 21:20:25 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_tok_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_INPUT,
	TOK_REDIR_OUTPUT,
	TOK_REDIR_APPEND,
	TOK_REDIR_HEREDOC,
}	t_tok_type;

typedef struct s_token
{
	t_tok_type		type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir_node
{
	t_redir_type		kind;
	char				*filename;
	struct s_redir_node	*next;
}	t_redir_node;

typedef struct s_tree
{
	t_node_type		kind;
	char			**argv;
	t_redir_node	*redirs;
	// int				pipes[2];
	// int				ambiguous;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

//libft
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int n);
void	*ft_malloc(size_t i);
void	ft_putstr_fd(char *s, int fd);
int		ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//syntaxe error
int		check_syntax_errors(t_token *token);
t_tree	*parse_tree(t_token **token);
void	print_tree(t_tree *tree, int depth);
#endif