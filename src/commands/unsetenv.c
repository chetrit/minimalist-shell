/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** unsetenv
*/

#include "minishell.h"
#include "env_utils.h"
#include "my_utils.h"

void unset_env_single(char **env, char **av)
{
    int cond = false;

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(av[1], env[i], my_strlen(av[1])) == 0)
            cond = true;
        if (cond)
            env[i] = env[i + 1];
    }
}

void unset_env(shell_t *shell, char **av)
{
    if (!av[1]) {
        my_put_error("unsetenv: Too few arguments.\n");
        shell->return_value = 1;
        return;
    }
    if (my_strcmp(av[1], "*") == 0) {
        shell->env = NULL;
        return;
    }
    for (; av[1] != NULL; av++) {
        unset_env_single(shell->env, av);
    }
}
