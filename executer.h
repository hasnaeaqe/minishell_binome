/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:23:42 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/07 20:29:04 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	ft_cd(char **argv);
void	ft_echo(char **argv);
t_env	*create_node(char *cle, char *val);
int		ft_strlen(char *s);
void	*ft_malloc(size_t i);
void	built_exit(char **args);
void	ft_pwd(void);
void	ft_putstr(char *s);
void	ft_printenv(t_env *head);
int		ft_isdigit(int c);
int		ft_atoi( char *str);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const  *s, char c);
char	*ft_strjoin(char  *s1, char  *s2);
char *find_cmd_path(char *cmd, char **env);
#endif