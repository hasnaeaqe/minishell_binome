#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*l;

	s = (unsigned char *)s1;
	l = (unsigned char *)s2;
	i = 0;
	while (s[i] == l[i] )
	{
		if (s[i] == '\0' || l[i] == '\0')
			return (0);
		i++;
	}
	return (s[i] - l[i]);
}
void handel_heredoc(char *delimiteur)
{
    char *line = NULL;
    int fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY );
    while (1) {
        line = readline("minishell$ ");
        if (!line || ft_strcmp(line, delimiteur) == 0) {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] != '\0' && haystack[i + j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("minishell$ ");
        if (!line) 
            break;
        if (*line)
            add_history(line);
        
        free(line);
        if (ft_strstr(line,"<<"))
            handel_heredoc("EOF");
    }
    return 0;
}
