#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction ft_strdup minimale (tu peux remplacer par la tienne)
char *ft_strdup(const char *s) {
    char *dup = malloc(strlen(s) + 1);
    if (!dup) return NULL;
    strcpy(dup, s);
    return dup;
}

// Fonction ft_strcmp minimale
int ft_strcmp(const char *s1, const char *s2) {
    return strcmp(s1, s2);
}

// Fonction ft_isalpha minimale
int ft_isalpha(int c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Structure pour l'environnement
typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;

// Création d'un nouveau nœud
t_env *create_node(char *key, char *value) {
    t_env *node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    node->key = ft_strdup(key);
    node->value = value ? ft_strdup(value) : NULL;
    node->next = NULL;
    return node;
}

// Conversion de env[] vers t_env *
t_env *ft_env(char **envp) {
    t_env *head = NULL;
    t_env *tmp = NULL;
    while (*envp) {
        char *eq = strchr(*envp, '=');
        if (eq) {
            char *key = ft_strdup(*envp);
            key[eq - *envp] = '\0';
            char *value = ft_strdup(eq + 1);
            t_env *new = create_node(key, value);
            if (!head)
                head = new;
            else
                tmp->next = new;
            tmp = new;
            free(key);
            free(value);
        }
        envp++;
    }
    return head;
}

// Calcul de la taille de la liste
int ft_lstsize(t_env *lst) {
    int size = 0;
    while (lst) {
        lst = lst->next;
        size++;
    }
    return size;
}

// Conversion liste -> tableau
t_env **env_to_array(t_env *env, int size) {
    t_env **array = malloc(sizeof(t_env *) * (size + 1));
    int i = 0;
    while (env && i < size) {
        array[i++] = env;
        env = env->next;
    }
    array[i] = NULL;
    return array;
}

// Comparaison pour qsort
int compare_env_nodes(const void *a, const void *b) {
    t_env *node_a = *(t_env **)a;
    t_env *node_b = *(t_env **)b;
    return ft_strcmp(node_a->key, node_b->key);
}

// Affichage au format declare -x ...
void ft_printexport(t_env *head) {
    while (head) {
        if (head->value)
            printf("declare -x %s=\"%s\"\n", head->key, head->value);
        else
            printf("declare -x %s\n", head->key);
        head = head->next;
    }
}

// Parsing de clé/valeur
char *ext_key(char *str) {
    int i = 0;
    while (str[i] && str[i] != '=' && str[i] != '+')
        i++;
    char *key = malloc(i + 1);
    if (!key)
        return NULL;
    strncpy(key, str, i);
    key[i] = '\0';
    return key;
}

char *ext_val(char *str) {
    char *eq = strchr(str, '=');
    if (!eq)
        return NULL;
    return ft_strdup(eq + 1);
}

// Parse mode (0: replace, 1: append, -1: invalid)
int parse_args(char *str) {
    int i = 0;
    while (str[i] && str[i] != '=' && str[i] != '+') {
        if (!ft_isalpha(str[i]))
            return -1;
        i++;
    }
    if (!str[i])
        return -1;
    if (str[i] == '+' && str[i + 1] == '=')
        return 1;
    return 0;
}

// Trouver un nœud par clé
t_env *find_node(t_env *env, char *key) {
    while (env) {
        if (ft_strcmp(env->key, key) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}

// Ajouter ou mettre à jour une variable
void add_to_env_or_update(t_env **env, char *key, char *value, int mode) {
    t_env *existing = find_node(*env, key);
    if (existing) {
        if (mode == 0) {
            free(existing->value);
            existing->value = ft_strdup(value);
        } else if (mode == 1) {
            char *tmp = existing->value;
            existing->value = ft_strjoin(tmp, value);
            free(tmp);
        }
        return;
    }

    t_env *new = create_node(key, value);
    if (!*env) {
        *env = new;
        return;
    }

    t_env *tmp = *env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

// Fonction principale export
void ft_add_export(char **argv, t_env **env) {
    int i = 1;
    while (argv[i]) {
        int mode = parse_args(argv[i]);
        char *key = ext_key(argv[i]);
        char *val = ext_val(argv[i]);

        if (key)
            add_to_env_or_update(env, key, val ? val : "", mode);
        else
            add_to_env_or_update(env, argv[i], "", mode);

        free(key);
        free(val);
        i++;
    }
}

// Export principal
void ft_export(int argc, char **argv, char **envp) {
    t_env *list = ft_env(envp);
    int size = ft_lstsize(list);
    t_env **array = env_to_array(list, size);

    // Tri avec qsort
    qsort(array, size, sizeof(t_env *), compare_env_nodes);

    if (argc == 1) {
        ft_printexport(list);
    } else {
        ft_add_export(argv, &list);
        array = env_to_array(list, ft_lstsize(list));
        qsort(array, ft_lstsize(list), sizeof(t_env *), compare_env_nodes);
        ft_printexport(*array);
    }
}

// Main
int main(int argc, char **argv, char **envp) {
    ft_export(argc, argv, envp);
    return 0;
}