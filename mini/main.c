int	ft_cd(char **argv, t_env *env)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	if (argv[1] == NULL)
		return (get_home(env));
	else if (ft_strcmp(argv[1], ".") == 0)
	{
		char *cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			perror("getcwd");
			return (1);
		}
		update_value(env, "OLDPWD", cwd);
		free(cwd);
		return (0);
	}

	path = argv[1];
	oldpwd = get_value(env, "PWD");
	if (oldpwd)
		update_value(env, "OLDPWD", oldpwd);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		update_value(env, "PWD", newpwd);
		free(newpwd);
	}
	return (0);
}
