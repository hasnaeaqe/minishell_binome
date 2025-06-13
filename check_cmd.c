/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:48:18 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/13 21:48:12 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int check_builts(char *cmd)
{
    if (!cmd)
        return (-1);
    if (ft_strcmp(cmd, "cd"))
        built_cd(cmd);
    else if (ft_strcmp(cmd, "echo"))
        built_echo(cmd);
    else if (ft_strcmp(cmd, "pwd"))
        built_pwd();
    else if (ft_strcmp(cmd, "unset"))
        built_echo(cmd);
    else if (ft_strcmp(cmd, "echo"))
        built_echo(cmd);
    
}