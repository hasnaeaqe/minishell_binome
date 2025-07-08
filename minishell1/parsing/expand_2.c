/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:48:12 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/08 15:30:56 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_export(t_token *token)
{
	char	*str;
	t_token	*tmp;
	int		i;
	int		check;

	if (!token)
		return ;
	tmp = token;
	if (ft_strcmp(tmp->value, "export") == 0 && tmp->next)
	{
		tmp = tmp->next;
		while (tmp)
		{
			if (tmp->type == TOK_WORD)
			{
				str = ft_strdup(tmp->value);
				i = 0;
				check = valide_key(str, &i);
				if (check == 0 && !ft_strchr(&str[i], '"')
					&& !ft_strchr(&str[i], '\''))
					tmp->value = add_quotes(str);
			}
			tmp = tmp->next;
		}
	}
}

int	handel_ambiguous(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == TOK_REDIR_APPEND || tmp->type == TOK_REDIR_INPUT
			|| tmp->type == TOK_REDIR_OUTPUT)
		{
			if (tmp->next && count_word(tmp->next->value, ' ') != 1)
			{
				tmp->ambig = 1;
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

void	replace_single_quote(int *i, int *j, char *value, char **total_str)
{
	(*total_str)[(*j)++] = value[(*i)++];
	while (value[*i] && value[*i] != '\'')
		(*total_str)[(*j)++] = value[(*i)++];
	if (value[*i] == '\'')
		(*total_str)[(*j)++] = value[(*i)++];
}

void	replace_double_quote(int *i, int *j,
	char *value, char **total_str, char *expand_value, char *dest)
{
	int	k;
	int	dest_len;

	dest_len = ft_strlen(dest);
	(*total_str)[(*j)++] = value[(*i)++];
	while (value[*i] && value[*i] != '"')
	{
		if (value[*i] == '$' && value[*i + 1]
			&& ft_strncmp(&value[*i + 1], dest, dest_len) == 0)
		{
			k = 0;
			if (expand_value)
			{
				while (expand_value[k])
					(*total_str)[(*j)++] = expand_value[k++];
			}
			*i += dest_len + 1;
		}
		else
			(*total_str)[(*j)++] = value[(*i)++];
	}
	if (value[*i] == '"')
		(*total_str)[(*j)++] = value[(*i)++];
}

void	replace_word(int *i, int *j, char *expand_value,
		char **total_str, int dest_len)
{
	int	k;

	k = 0;
	if (expand_value)
	{
		while (expand_value[k])
			(*total_str)[(*j)++] = expand_value[k++];
	}
	(*i) += dest_len + 1;
}
