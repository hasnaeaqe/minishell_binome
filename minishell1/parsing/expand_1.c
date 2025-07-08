/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:40:34 by cbayousf          #+#    #+#             */
/*   Updated: 2025/07/08 15:14:25 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_value(int *i, char *str)
{
	int		j;
	char	*dest;

	j = 0;
	dest = ft_malloc((*i + 1) * sizeof(char));
	if (j == (*i) - 1)
		dest[j++] = str[*i];
	else
	{
		while (j < *i - 1)
		{
			dest[j] = str[j + 1];
			j++;
		}
	}
	dest[j] = '\0';
	return (dest);
}

static char	*find_expand(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = 1;
	j = 0;
	if (!str || str[0] != '$' )
		return (ft_strdup(""));
	if (str[1] == '?')
		return (ft_strdup("?"));
	if (ft_isdigit(str[i]))
	{
		dest = ft_malloc(2 * sizeof(char));
		dest[j++] = str[i];
		dest[j] = '\0';
		return (dest);
	}
	while (str[i]
		&& (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
		i++;
	return (expand_value(&i, str));
}

static char	*extract_value(char *dest, t_env *env)
{
	if (!dest)
		return (ft_strdup(""));
	if (ft_strcmp(dest, "?") == 0)
		return (ft_itoa(exit_status(0, 1)));
	while (env)
	{
		if (ft_strcmp(env->key, dest) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

static char	*transform_to_gar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = ' ';
		else if (str[i] == '\t')
			str[i] = ' ';
		else
			str[i] = str[i] * (-1);
		i++;
	}
	return (str);
}

char	*expand(char *src, char *str, t_env *env, int flag)
{
	char	*dest;
	char	*expand_value;
	size_t	len;
	size_t		count;

	dest = find_expand(str);
	// if (!dest)
	// 	return (NULL);////zdt hna
	expand_value = transform_to_gar(extract_value(dest, env));
	// if (!expand_value)
	// 	return (NULL);////zdt hna
	count = count_expand(src, dest, flag);
	len = ft_strlen(src) - ft_strlen(dest) * count + ft_strlen(expand_value) * count - count;
	// printf("count : %d\n",count);
    // printf("len :%d\n",len);
	// printf("value : %s,str : %s  dest: %s , exapnd : %s \n",src,str,dest,expand_value);
	return (rwina(src, dest, expand_value, len, flag));
}
