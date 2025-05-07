#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Fonction pour découper une commande en tableau d'arguments
char **split_command(const char *cmd) {
    char **args = malloc(64 * sizeof(char *));
    char *cmd_copy = strdup(cmd);
    char *token = strtok(cmd_copy, " ");
    int i = 0;

    while (token != NULL) {
        args[i++] = strdup(token);
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    free(cmd_copy);
    return args;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s \"commande1\" \"commande2\"\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Découpe des commandes
    char **cmd1 = split_command(argv[1]);
    char **cmd2 = split_command(argv[2]);

    // Premier processus : commande 1 (écriture dans le pipe)
    pid1 = fork();
    if (pid1 == 0) {
        close(pipefd[0]); // Ferme la lecture
        dup2(pipefd[1], STDOUT_FILENO); // Redirige stdout vers le pipe
        close(pipefd[1]);
        execvp(cmd1[0], cmd1);
        perror("execvp cmd1");
        exit(EXIT_FAILURE);
    }

    // Deuxième processus : commande 2 (lecture depuis le pipe)
    pid2 = fork();
    if (pid2 == 0) {
        close(pipefd[1]); // Ferme l'écriture
        dup2(pipefd[0], STDIN_FILENO); // Redirige stdin depuis le pipe
        close(pipefd[0]);
        execvp(cmd2[0], cmd2);
        perror("execvp cmd2");
        exit(EXIT_FAILURE);
    }

    // Parent : ferme les deux extrémités du pipe
    close(pipefd[0]);
    close(pipefd[1]);

    // Attend que les deux enfants terminent
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    // Libère la mémoire
    for (int i = 0; cmd1[i]; i++) free(cmd1[i]);
    for (int i = 0; cmd2[i]; i++) free(cmd2[i]);
    free(cmd1);
    free(cmd2);

    return 0;
}
