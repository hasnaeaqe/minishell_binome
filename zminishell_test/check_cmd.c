/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:48:18 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/19 10:51:41 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int check_builts(t_tree *tree)
{
    char *cmd;

    if (!tree)
        return (-1);
    cmd = tree->argv;
    if (ft_strcmp(cmd, "cd"))
        built_cd(cmd);
    else if (ft_strcmp(cmd, "echo"))
        ft_echo(cmd);
    else if (ft_strcmp(cmd, "pwd"))
        built_pwd();
    // else if (ft_strcmp(cmd, "unset"))
    //     ft_unset(cmd);
    // else if (ft_strcmp(cmd, "echo"))
    //     ft_echo(cmd);
}