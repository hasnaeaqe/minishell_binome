/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:41:22 by haqajjef          #+#    #+#             */
/*   Updated: 2025/06/19 19:07:18 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static void	ft_free(void *p, int k)
{
	static void		*lst[INT_MAX];
	static size_t	i;

	if (k)
	{
		while (lst[i])
			free(lst[i--]);
	}
	else
		lst[i++] = p;
}

void	ft_exit(int n)
{
	ft_free(NULL, 1);
	exit(n);
}

void	*ft_malloc(size_t i)
{
	void	*k;

	k = malloc(i);
	if (!k)
		ft_exit(1);
	ft_free(k, 0);
	return (k);
}

size_t ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
void	ft_strncpy(char *dest, char *src, int n)
{
	int i;
	i = 0;
	while(i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
char	*ft_strdup( const char *s1)
{
	int		lens1;
	int		i;
	char	*tab;

	lens1 = ft_strlen(s1);
	tab = malloc ((lens1 + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
t_env	*create_node(char *cle, char *val)
{
	t_env	*env;

	env = ft_malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = cle;
	env->value = val;
	env->next = NULL;
	return (env);
}

char *ext_key(char *str) {
    int i = 0;
    while (str[i] && str[i] != '=' && str[i] != '+')
        i++;
    char *key = ft_malloc(sizeof(char) *(i + 1));
    ft_strncpy(key, str, i);
	key[i] = '\0';
    return key;
}

char	*ext_val(char *env)
{
	char *equal;
	char *val;

	equal = ft_strchr(env, '=');
	if(!equal)
		return(NULL);
	val = ft_strdup(equal + 1);
	return (val);
}

void	ft_printenv(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if(tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

t_env *ft_env(char **env)
{
	t_env	*ev;
	t_env	*new_node;
	t_env	*head;
	int		i;

	ev = NULL;
	head = NULL;
	i = 0;
	new_node = create_node(ext_key(env[i]), ext_val(env[i]));
	head = new_node;
	ev = head;
	while (env[i])
	{
		new_node = create_node(ext_key(env[i]), ext_val(env[i]));
		ev->next = new_node;
		ev = new_node;
		i++;
	}
	return (head);
}
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
char *get_value(t_env *env, char *key)
{
	t_env *head = env;
	while(head && head->next)
	{
		// printf("%s\n", head->key);
		if(ft_strcmp(head->key, key) == 0)
		{
			return (head->value);
		}
		head = head->next;
	}
	return (NULL);
}
void update_value(t_env *env, char *key, char *value)
{
	t_env *new;

	while(env)
	{
		if(ft_strcmp(env->key, key))
			env->value = ft_strdup(value);
		env = env->next;
	}
	new = create_node(key, value);
	new->next = env;
	new = env;
}
int	ft_cd(char **argv, t_env *env)
{
	int		r;
	char	*path;// const ? because we could change the original value without intending to
	char buf[1024];
	if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0 )
	{
		printf("hello\n");
		path = get_value(env, "HOME");
		printf("%s\n", path);
		if(!path)
		{
			perror("path");
			exit(1);
		}
	}
	else if (argv[1] && ft_strcmp(argv[1], "-") == 0)
	{
		// path = get_value(env, "PWD");
		// if(!path)
		// {
		// 	perror("path");
		// 	exit(1);
		// }
		printf("%s/n", get_value(env, "OLDPWD"));
	}
	else if (argv[1] && ft_strcmp(argv[1], "..") == 0)
	{
		path = argv[1];
		r = chdir(path);
		if (r == -1)
		{
			perror("operation echoue!");
		}
	}
	else if (argv[1] && ft_strcmp(argv[1], ".") == 0)
	{
		path = getcwd(buf, sizeof(buf));
		if(!path)
		{
			perror("path");
			exit(1);
		}
		update_value(env, "OLDPWD", path);
		printf("oldpwd:%s\n",get_value(env, "OLDPWD"));
		return (0);
	}
	path = argv[1];
	r = chdir(path);
	if (r == -1)
	{
		ft_putstr_fd("minishell: cd: ",2);
		ft_putstr_fd(path,2);
		ft_putstr_fd(": No such file or directory\n",2);
	}
	return (0);
}

int	main(int argc, char**argv ,char **envp)
{
	t_env *env = ft_env(envp);
	// ft_printenv(env);
	// printf("----%s\n", get_value(env, "HOME"));

	// while(1)
	// {
		ft_cd(argv, env);
		printf("cwd %s\n",getcwd(NULL, 0));
	// }	
}
