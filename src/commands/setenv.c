/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** setenv
*/

#include "minishell.h"
#include "my_utils.h"
#include "env_utils.h"

int env_exists(char **env, char **av)
{
    char *tmp = NULL;

    if (!env)
        return (0);
    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(av[1], env[i], my_strlen(av[1])) == 0) {
            tmp = env[i];
            tmp[my_strlen(av[1]) + 1] = '\0';
            env[i] = malloc(sizeof(char) * (my_strlen(tmp) + my_strlen(av[2])));
            env[i] = my_strcat(tmp, av[2]);
            return (1);
        }
    }
    return (0);
}

int my_str_isalphanum(char const *str)
{
    int len = my_strlen(str);

    for (int i = 0; i != len; i += 1) {
        if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') &&
            (str[i] > '9' || str[i] < '0'))
            return (0);
    }
    return (1);
}

int check_error_setenv(shell_t *shell, char **av)
{
    if (!av[1] || (av[2] && av[3])) {
        !av[1] ? print_env(shell->env)
            : my_put_error("setenv: Too many arguments.\n");
        return (1);
    }
    if ((av[1][0] < 'a' || av[1][0] > 'z') && (av[1][0] < 'A'
        || av[1][0] > 'Z') && (av[1][0] > '9' || av[1][0] < '0')) {
        my_put_error("setenv: Variable name must begin with a letter.\n");
        return (1);
    }
    if (!my_str_isalphanum(av[1])) {
        my_put_error("setenv: Variable name must "
                    "contain alphanumeric characters.\n");
        return (1);
    }
    return (0);
}

void set_env(shell_t *shell, char **av)
{
    char **new_env = NULL;
    int i = 0;
    int j = 0;

    if (check_error_setenv(shell, av)) {
        shell->return_value = 84;
        return;
    }
    if (av[2] && env_exists(shell->env, av)) {
        return;
    }
    for (; shell->env && shell->env[i] != NULL; i++);
    new_env = malloc(sizeof(char *) * (i + 2));
    for (; j < i; j++)
        new_env[j] = my_strdup(shell->env[j]);
    new_env[j] = !av[2] ? my_strcat(av[1], "=")
        : my_strcat(my_strcat(av[1], "="), av[2]);
    new_env[j + 1] = NULL;
    shell->env = new_env;
}