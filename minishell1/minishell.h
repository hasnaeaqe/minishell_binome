/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:33:22 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/02 16:12:04 by haqajjef         ###   ########.fr       */
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
#include <errno.h>
#include <sys/stat.h>


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
	int					ishd;
	int					flag;
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
char	*ft_strdup(char *s1);
char	*ft_strndup(char *s1, int n);
void	*ft_malloc(size_t i);
void	ft_putstr_fd(char *s, int fd);
int		ft_stchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_strjoin(char  *s1, char  *s2);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
void	ft_strncpy(char *dest, char *src, int n);
long	ft_atoi( char *str);
int		ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_str(char *s);
void    ft_lstadd_back(t_env **lst, t_env *new);
int	ft_lstsize(t_env *lst);
int		ft_count(char const *s, char c);
char	*ft_itoa(int n);
int	ft_isascii(int c);
char *ft_strjoin_3(char *s1, char *s2, char *s3);
//parsing
int		check_syntax_errors(t_token *token);
t_tree	*parse_tree(t_token **token,int flag);
void	print_tree(t_tree *tree, int depth);
void	tokenisation(char *str, t_token **token);
void	print_tokens(t_token *token);
void	free_tokens(t_token *token);
void	expand_tokens(t_token **token, t_env *env);
int		 remove_quotes(t_token **token);
char	*expand_heredoc(char *line, t_env *env);
int		handel_ambiguous(t_token **token);
int exit_status(int status, int flag);
//exection
char	*find_cmd_path(char *cmd, t_env *env);
t_env	*create_node(char *cle, char *val);
char	*ext_key(char *str);
char	*ext_val(char *env);
void	ft_printenv(t_env **head);

t_env	**env_to_array(t_env *env, int size);
int parse_args(char *str);
int exit_status(int status, int flag);

t_env	*ft_env(char **env);
t_env	*env_vide();
void	set_old_to_null(t_env **env);

int		ft_echo(char **argv);
int		built_pwd(t_env *env, int write);
void	built_exit(char **args);
int		ft_unset(t_env **head, char **key_to_unset);
//export
int		ft_export(char **argv, t_env **env);
void	sort_list(t_env **env);
void	ft_printexport(t_env **head);
t_env	*find_node(t_env *env, char *key);
//cd
int		ft_cd(char **argv, t_env *env);
char	*get_value(t_env *env, char *key);
void	update_value(t_env *env, char *key, char *value);
char	*remove_last_slash(char *path);
void	erreur(char *dir);
//built_exec
int is_builtins(char *cmd);
int check_builts(t_tree *tree,t_env **env);

int    handle_redirs(t_tree *tree);
void	handle_heredoc(t_tree *tree, t_env *env);

void errors(char *cmd, int mode);
int	is_directory(char *path);
void	put_errno(char *dir);
int		exec_tree(t_tree *tree, t_env **env);
#endif