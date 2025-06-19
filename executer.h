/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:23:42 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/19 10:42:27 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>

# include <string.h>


typedef struct s_env
{
	char			*key;
	char			*value;			
	struct s_env	*next;
}	t_env;

void	built_cd(char **argv);
void	ft_echo(char **argv);
t_env	*ft_env(char **env);
void	built_pwd(void);
void	built_exit(char **args);
void	ft_export(int argc, char **argv, char **env);
void	ft_unset(t_env **head, char **key_to_unset);
t_env	*create_node(char *cle, char *val);
size_t ft_strlen(const char *s);
void	*ft_malloc(size_t i);
void	ft_putstr(char *s);
void	ft_printenv(t_env *head);
int		ft_isdigit(int c);
long		ft_atoi( char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const  *s, char c);
char	*ft_strjoin(char  *s1, char  *s2);

void	execute_2cmd(char **argv, char **env);
char	*ext_val(char *env);
char	*ext_key(char *env);
int		check_key(char *str);
int		ft_isalpha(int c);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
void	ft_strncpy(char *dest, char *src, int n);
void	execute(char **argv, char **env);


#endif