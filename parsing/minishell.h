/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:33:22 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/19 16:59:09 by haqajjef         ###   ########.fr       */
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

#include <string.h>
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
	int					fd;
	int				ishd;
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

typedef struct s_env
{
	char			*key;
	char			*value;			
	struct s_env	*next;
}	t_env;

//libft
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int n);
void	*ft_malloc(size_t i);
void	ft_putstr_fd(char *s, int fd);
int		ft_stchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//syntaxe error
int		check_syntax_errors(t_token *token);
t_tree	*parse_tree(t_token **token);
void	print_tree(t_tree *tree, int depth);
void	tokenisation(char *str, t_token **token);
void	print_tokens(t_token *token);
void	free_tokens(t_token *token);

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char  *s1, char  *s2);
char	*find_cmd_path(char *cmd, char **env);
t_env	*create_node(char *cle, char *val);
void	built_cd(char **argv);
void	ft_echo(char **argv);
// t_env	*ft_env(char **env);
void	built_pwd(void);
// void	built_exit(char **args);
// void	ft_export(int argc, char **argv, char **env);
// void	ft_unset(t_env **head, char **key_to_unset);
void	ft_putstr(char *s);
int exec_tree(t_tree *tree, char **env);
void free_tree(t_tree *tree);

#endif