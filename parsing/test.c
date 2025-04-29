#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *line = readline("minishell$ ");
    if (line && *line)
        add_history(line);

    printf("You entered: %s\n", line);
    free(line);
    return 0;
}
