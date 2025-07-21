/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:33:22 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/21 15:25:32 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define RL_NO_COMPAT
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>

extern int	g_signal;

typedef enum e_fd
{
	OPEN,
	CLOSE,
	HER_DOC,
}	t_fd;

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
	int				ambig;
	char			*value;
	t_tok_type		type;
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

typedef struct s_replace_ctx
{
	char	*value;
	char	*expand_value;
	char	*dest;
	int		start;
	char	*str;
	int		i;
}	t_replace_ctx;

typedef struct s_redir_node
{
	int					fd;
	int					ishd;
	int					flag;
	int					ambiguous;
	char				*filename;
	t_redir_type		kind;
	struct s_redir_node	*next;
}	t_redir_node;

typedef struct s_tree
{
	char			**argv;
	t_node_type		kind;
	t_redir_node	*redirs;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_env
{
	char			*key;
	char			*value;			
	struct s_env	*next;
}	t_env;

typedef struct s_exec
{
	int	fd_in;
	int	fd_out;
}	t_exec;

typedef struct s_close_fds
{
	int					fd;
	int					kind;
	char				*filename;
	struct s_close_fds	*next;
}	t_close_fds;

char			*ft_strdup(char *s1);
char			*ft_strndup(char *s1, size_t n);
void			*ft_malloc(size_t i);
void			ft_putstr_fd(char *s, int fd);
int				ft_stchr(const char *s, int c);
size_t			ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
long			ft_atoi( char *str, int *overflow);
int				ft_strnstr(const char *haystack,
					const char *needle, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			ft_lstadd_back(t_env **lst, t_env *new);
int				ft_lstsize(t_env *lst);
int				ft_count(char const *s, char c);
char			*ft_itoa(int n);
int				ft_isascii(int c);
char			*ft_strjoin_3(char *s1, char *s2, char *s3);
void			ft_free(void *p, int k);

int				count_word(char *s, char c);
int				count_quote(char *src);
void			setup_signals(void);
char			*rm_quotes(char *src);
void			max_herdoc(t_token *token);
void			tokenisation(char *str, t_token **token);
t_token			*new_token(t_tok_type type, char *value);
int				check_syntax_errors(t_token *token);
int				is_redi_operator(t_tok_type type);
int				open_quotes(char *str, int *i);
void			free_tokens(t_token *token);
void			expand_tokens(t_token **token, t_env *env);
void			check_export(t_token *token);
int				valide_key(char *str, int *i);
char			*add_quotes(char *str);
char			*expand(char *src, char *str, t_env *env, int flag);
size_t			count_expand(char *src, char *dest, int flag);
char			*replace_expand_value(t_replace_ctx *ctx, size_t len, int flag);
void			replace_single_quote(size_t *i, size_t *j,
					char *value, char **total_str);
void			replace_double_quote(size_t *i, size_t *j,
					char **total_str, t_replace_ctx *ctx);
void			replace_word(size_t *i, size_t *j, char **total_str,
					t_replace_ctx *ctx);
int				handel_ambiguous(t_token **token);
void			skip_single_double_quote(char *str, int *i);
void			splite_expand(t_token **token);
int				flag_herdoc(t_token **token);
t_tree			*parse_tree(t_token **token, int flag);
t_tree			*parse_commande(t_token **token, int flag);
int				count_quote(char *src);
char			*trasform_garbeg(char *str);
t_redir_node	*new_redir(t_redir_type kind, char *filename,
					int flag, int ambiguous);
t_tree			*new_tree(t_node_type kind, char **argv, t_redir_node *redirs);
void			print_tree(t_tree *tree, int depth);
void			print_tokens(t_token *token);
char			*expand_heredoc(char *line, t_env *env, int flag);
int				exit_status(int status, int flag);
int				is_redi_operator(t_tok_type type);
int				word_error(t_token *tmp);
void			handel_case(t_token **token);
void			handel_signal(void);
char			*find_cmd_path(char *cmd, t_env *env, int *status);
t_env			*create_node(char *cle, char *val);
char			*ext_key(char *str);
char			*ext_val(char *env);
void			ft_printenv(t_env **head);
t_env			**env_to_array(t_env *env, int size);
int				parse_args(char *str);
int				exit_status(int status, int flag);
t_env			*ft_env(char **env);
t_env			*env_vide(void);
int				ft_echo(char **argv);
int				built_pwd(t_env *env, int write);
int				built_exit(char **args, int is_child);
int				ft_unset(t_env **head, char **key_to_unset);
int				ft_export(char **argv, t_env **env);
void			sort_list(t_env **env);
void			ft_printexport(t_env **head);
t_env			*find_node(t_env *env, char *key);
t_env			**env_to_array(t_env *env, int size);
int				ft_cd(char **argv, t_env *env);
char			*get_value(t_env *env, char *key);
void			update_value(t_env *env, char *key, char *value);
char			*remove_last_slash(char *path);
int				erreur(char *dir);
int				is_builtins(char *cmd);
int				check_builts(t_tree *tree, t_env *env, int is_child);
char			*check_in_paths(char **dirs, char *cmd);
void			ft_free_tab(char **tab);
int				handle_redirs(t_tree *tree);
int				handle_heredoc(t_tree *tree, t_env *env, int *stop_herdoc);
int				errors(char *cmd, int mode);
int				is_directory(char *path);
int				exec_tree(t_tree *tree, t_env **env, int is_child);
char			**to_array(t_env *env, int size);
void			handle_heredoc_signals(void);
char			*generate_filename(void);
void			write_in_herdoc(t_redir_node *redir, t_env *env, int fd);
int				count_dolar(char *delimiter);
void			reset_terminal_mode(void);
int				status_exit(int status);
int				execute_pipe(t_tree *tree, t_env *env);
int				open_fds(char *filename, int flag, int option, int Kind);
int				get_home(char **argv, t_env *env);
#endif