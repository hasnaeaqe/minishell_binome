/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:35 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/19 10:44:33 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while(s1[i] && s2[i])
	{
		if(s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

void	unset_one(t_env **head, char *key_to_unset)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *head;
	prev = NULL;
	if (!tmp)
		return;
	if (tmp && ft_strcmp(tmp->key, key_to_unset) == 0)
	{
		*head = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return ;
	}
	while (tmp && ft_strcmp(tmp->key, key_to_unset) != 0)
	{
		prev = tmp;
		tmp =tmp->next;
	}
	if(!tmp)
		return;
	prev->next = tmp->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}
void ft_unset(t_env **head, char **key_to_unset)
{
	int i = 0;
	while(key_to_unset[i])
	{
		unset_one(head, key_to_unset[i]);
		i++;
	}
}
// int main()
// {
//     t_env *head = create_node("user", "haqajjef");
//     head->next = create_node("PATH", "mnt/homes/haqajjef/.docker");
//     head->next->next = create_node("SHELL", "/bin/zsh");

// char *str = "user";
//     ft_printenv(head);
//     ft_unset(&head, &str);
//     ft_printenv(head);
// }

// int main()
// {
//     t_env *head = create_node(strdup("USER"), strdup("haqajjef"));
//     head->next = create_node(strdup("PATH"), strdup("/usr/bin"));
//     head->next->next = create_node(strdup("SHELL"), strdup("/bin/zsh"));

//     char *to_delete = "USER";

//     ft_printenv(head);
//     printf("---- Après unset ----\n");
//     ft_unset(&head, &to_delete);
//     ft_printenv(head);

//     return 0;
// }

int main()
{
    t_env *head = create_node(strdup("USER"), strdup("haqajjef"));
    head->next = create_node(strdup("PATH"), strdup("/usr/bin"));
    head->next->next = create_node(strdup("SHELL"), strdup("/bin/zsh"));
    head->next->next->next = create_node(strdup("EDITOR"), strdup("vim"));

    printf("Avant unset :\n");
    ft_printenv(head);

    printf("\nAprès unset USER et EDITOR :\n");
    char *to_unset[] = {"USER", "EDITOR", NULL};
    ft_unset(&head, to_unset);

    ft_printenv(head);

    return 0;
}
