/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:47:29 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/08 15:14:37 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_quotes(char *str)
{
	char	*dest;
	int		i;

	i = 0;
	// if (!str)
	// 	return (NULL);
	dest = ft_malloc((ft_strlen(str) + 3) * sizeof(char));
	while (*str && *str != '=' && *str != '+')
		dest[i++] = *str++;
	if (*str == '+')
		dest[i++] = *str++;
	if (*str == '=')
		dest[i++] = *str++;
	dest[i++] = '"';
	while (*str)
		dest[i++] = *str++;
	dest[i++] = '"';
	dest[i] = '\0';
	return (dest);
}

int	valide_key(char *str, int *i)
{
	int	check;

	check = 0;
	while (str[*i] && str[*i] != '=')
	{
		if (str[*i] == '+' && str[*i + 1] == '=')
			break ;
		if (ft_isdigit(str[0])
			|| (!ft_isalpha(str[*i]) && !ft_isdigit(str[*i]) && str[*i] != '_'))
		{
			check = 1;
			break ;
		}
		(*i)++;
	}
	return (check);
}

static void	skip_quote(char *src, int *i)
{
	(*i)++;
	while (src[*i] && src[*i] != '\'')
		(*i)++;
	if (src[*i] == '\'')
		(*i)++;
}

static void	count_in_quote(int *i, int *count, char *src, char *dest)
{
	int	dest_len;

	dest_len = ft_strlen(dest);
	(*i)++;
	while (src[*i] && src[*i] != '"')
	{
		if (src[*i] == '$' && src[*i + 1]
			&& ft_strncmp(&src[*i + 1], dest, dest_len) == 0)
		{
			*i += ft_strlen(dest);
			(*count)++;
		}
		(*i)++;
	}
	if (src[*i] == '"')
		(*i)++;
}

size_t	count_expand(char *src, char *dest, int flag)
{
	int	dest_len;
	int	i;
	int	count;

	dest_len = ft_strlen(dest);
	i = 0;
	count = 0;
	while (src[i])
	{
		if (src[i] == '\'' && flag == 0)
			skip_quote(src, &i);
		else if (src[i] == '"')
			count_in_quote(&i, &count, src, dest);
		else if (src[i] == '$' && src[i + 1]
			&& ft_strncmp(&src[i + 1], dest, dest_len) == 0)
		{
			count++;
			i++;
			i += ft_strlen(dest);
		}
		else
			i++;
	}
	return (count);
}
