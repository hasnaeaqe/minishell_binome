/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:46:03 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/11 10:35:11 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

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

void ft_free_tab(char **tab)
{
	int i;

	i = 0;
	if(!tab[i])
		return ;
	while(tab[i])
		free(tab[i++]);
	free(tab);
}
char *find_cmd_path(char *cmd, char **env)
{
	(void) env;
	char *tmp;
	char *full_path;
	int i;

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
			ft_free_tab(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	full_path = ft_strjoin("./", cmd);
	if (access(full_path, X_OK) == 0)
	{
		ft_free_tab(dirs);
		return (full_path);
	}
	ft_free_tab(dirs);
	return NULL;
}

void execute_cmd(char **argv, char **env)
{
	pid_t pid;
	char *path;

	pid = fork();
	if(pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		path = find_cmd_path(argv[1], env);
		if(!path)
		{
			perror("Commande introvable!");
			exit(1);
		}
		if (execve(path, argv + 1, env) == -1)
		{
			perror("execv");
			free(path);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
	}
}

// int main(int ac, char **av, char **env)
// {
// 	if (ac < 2)
// 		return(1);
// 	execute_cmd(av, env);
// 	sleep(10); // temps pour analyser avec leaks
// 	return 0;
// }