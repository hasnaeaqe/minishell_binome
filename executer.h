/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:23:42 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/03 21:42:30 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
#define EXECUTER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	ft_cd(char **argv);
void	ft_echo(char **argv);
t_env	*create_node(char *cle, char *val);
int	ft_strlen(char *s);
void	*ft_malloc(size_t i);
void 	exi(int n);
void	ft_pwd(void);
void	ft_putstr(char *s);
void	ft_printenv(t_env *head);

#endif