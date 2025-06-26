/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0002/06/26 15:32:34 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/26 15:39:10 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int parse_args(char *str)
{
    int i;

    if (!str)
        return (-1);
    if(!ft_isalpha(str[0]) || str[0] != '_' || ft_isdigit(str[0]))
        return (-1);
    i = -1;
    while(str[i])
    {
        if(!ft_isalpha(str[i]) || str[i] != '_' || !ft_isdigit(str[i]))
            return (1);
        i++;
    }
    if (str[i] == '+' && str[i + 1] == '=')
		return (1);
    return (0);
}