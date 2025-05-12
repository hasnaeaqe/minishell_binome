#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include "../executer.h" // assuming ft_atoi is declared here or elsewhere

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
#include <limits.h>
#include <stdio.h>

int	ft_atoi(char *str)
{
    int			i;
    long long	c;
    int			signe;

    i = 0;
    c = 0;
    signe = 1;

    // Skip espaces
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;

    // Signe
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            signe = -1;
        i++;
    }

    // Vérifie qu'il y a bien des chiffres après
    if (!str[i])
        return (0);

    // Conversion
    while (str[i] >= '0' && str[i] <= '9')
    {
        int digit = str[i] - '0';

        // Vérifie overflow
      if ((signe == 1 && c > (LONG_MAX - digit) / 10) ||
    (signe == -1 && c > (-(long long)LONG_MIN - digit) / 10))
{
    fprintf(stderr, "exit: numeric argument required\n");
    exit(255);
}

        c = c * 10 + digit;
        i++;
    }

    return ((int)(signe * c));
}
int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_numeric(char *str)
{
    int	i;

    if (!str || !*str)
        return (0);
    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return (0); // sign only is invalid
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void	built_exit(char **args)
{
    long	exit_code;

    printf("exit\n");
    if (args[1])
    {
        if (!is_numeric(args[1]))
        {
            fprintf(stderr, "exit: %s: numeric argument required\n", args[1]);
            exit(255);
        }
        exit_code = ft_atoi(args[1]);
        if (args[2])
        {
            fprintf(stderr, "exit: too many arguments\n");
            return ; // don't exit yet, just return from function
        }
        exit((int)(exit_code & 0xFF)); // Only 8 bits used for exit status
    }
    exit(0);
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		built_exit(argv);
	else
		built_exit(NULL);
	return (0);
}
