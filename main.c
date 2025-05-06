/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:46:03 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/06 17:21:42 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

// char *get_path_from_env(char **env)
// {
// 	int i;
// 	i = 0;
// 	while(env[i])
// 	{
// 		if(strncmp(env[i],"PATH=", 5))
// 		{
// 			return (env[i] + 5);
// 		}
// 		i++;
// 	}
// 	return NULL;
// }

char *find_cmd_path(char *cmd, char **env)
{
	(void) env;
	char *tmp;
	char *full_path;
	int i;
	int j;

	// char *path = get_path_from_env(env);
	// if (path == NULL)
	// 	return (NULL);
	char *paths = getenv("PATH");
	char **dirs = ft_split(paths, ':');
	if(!dirs)
		return (NULL);
	i = 0;
	while(dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);

		if (access(full_path, X_OK) == 0)
		{
			j = 0;
			while(dirs[j])
			{
				free(dirs[j]);
				j++;
			}
			return (full_path);
		}
		free(full_path);
		i++;
	}
	j = 0;
	while(dirs[j])
	{
		free(dirs[j]);
		j++;
	}
	return NULL;
}


int main(int ac, char **av, char **env)
{
	if (ac != 2)
		return(1);
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return 1;
	}
	else if (pid == 0)
	{
		printf("je suis l enfant,j execute %s\n", av[1]);
		char *cmd_path = find_cmd_path(av[1], env);
		if (!cmd_path)
		{
			perror("Commande introuvable");
			exit(1);
		}

		// Crée le tableau d’arguments : av[1] et NULL
		char *args[] = {av[1],av[2] NULL};

		// Lance la commande
		if (execve(cmd_path, args, env) == -1)
		{
			perror("execve");
			free(cmd_path); // on libère si execve échoue
			exit(1);
		}
	}
	else
	{
		wait(NULL);
		printf("Je suis le parent. L'enfant a terminé.\n");
	}
	 return 0;
}

