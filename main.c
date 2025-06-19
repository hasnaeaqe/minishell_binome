// #include "executer.h"
// int main()
// {
//     while (1)
//     {
//         char *line = readline();
//         char **tmp = ft_split(line, ' ');
//         int i = 0;
//         while(tmp[i])
//         {
//             if(tmp[i] == "exit")
//                 built_exit(tmp);
//         }
//     }
// }
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ft_cd(char **argv, t_env **env)
{
    char *path;
    char oldpwd[1024];

    // Cas cd ou cd ~
    if (!argv[1] || strcmp(argv[1], "~") == 0)
    {
        path = get_env_value(*env, "HOME");
        if (!path)
        {
            fprintf(stderr, "cd: HOME non défini\n");
            return;
        }
    }
    // cd -
    else if (strcmp(argv[1], "-") == 0)
    {
        path = get_env_value(*env, "OLDPWD");
        if (!path)
        {
            fprintf(stderr, "cd: OLDPWD non défini\n");
            return;
        }
        printf("%s\n", path);
    }
    // cd chemin normal
    else
    {
        path = argv[1];
    }

    // Enregistrer ancien chemin
    if (!getcwd(oldpwd, sizeof(oldpwd)))
    {
        perror("getcwd");
        return;
    }

    if (chdir(path) == -1)
    {
        perror("cd");
        return;
    }

    // Mettre à jour OLDPWD et PWD
    set_env_value(env, "OLDPWD", oldpwd);
    char newpwd[1024];
    if (getcwd(newpwd, sizeof(newpwd)))
        set_env_value(env, "PWD", newpwd);
}
t_env *init_env(char **envp)
{
    t_env *head = NULL;
    int i = 0;

    while (envp[i])
    {
        char *sep = strchr(envp[i], '=');
        if (sep)
        {
            *sep = '\0';
            set_env_value(&head, envp[i], sep + 1);
            *sep = '='; // on restaure la string si besoin
        }
        i++;
    }
    return head;
}
