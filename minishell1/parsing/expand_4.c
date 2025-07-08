/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:05:05 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/08 12:42:44 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	loop_rwina(char *value, char *dest, char *expand_value,
	char **total_str, int flag, int *j)
{
	int	i;
	int	dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	while (value[i])
	{
		if (value[i] == '\'' && flag == 0)
			replace_single_quote(&i, j, value, total_str);
		else if (value[i] == '"')
			replace_double_quote(&i, j, value, total_str,
				expand_value, dest);
		else if (value[i] == '$' && value[i + 1]
			&& ft_strncmp(&value[i + 1], dest, dest_len) == 0)
				replace_word(&i, j, expand_value, total_str, dest_len);
		else
			(*total_str)[(*j)++] = value[i++];
	}
}

char	*rwina(char *value, char *dest, char *expand_value, int len, int flag)
{
	char	*total_str;
	int		j;

	// if (!value || !dest)
	// 	return (NULL);
	total_str = ft_malloc((len + 1) * sizeof(char));
	j = 0;
	loop_rwina(value, dest, expand_value, &total_str, flag, &j);
	total_str[j] = '\0';
	return (total_str);
}

t_redir_node	*new_redir(t_redir_type kind,
	char *filename, int flag, int ambiguous)
{
	t_redir_node	*new;

	new = ft_malloc(sizeof(t_redir_node));
	new->kind = kind;
	if (count_quote(filename) == 1)
		new->filename = ft_strdup("");
	else
		new->filename = trasform_garbeg(ft_strdup(filename));
	new->flag = flag;
	new->ambiguous = ambiguous;
	new->next = NULL;
	return (new);
}

t_token	*new_token(t_tok_type type, char *value)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token));
	new->type = type;
	new->ambig = 0;
	new->value = ft_strdup(value);
	if (!new)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}
