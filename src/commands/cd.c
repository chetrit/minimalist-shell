/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** cd
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "minishell.h"
#include "my_utils.h"
#include "env_utils.h"

void format_arr(shell_t *shell);

char **get_arr(char *s1, char *s2, char *s3)
{
    char **av = malloc(sizeof(char *) * 4);

    av[0] = my_strdup(s1);
    av[1] = my_strdup(s2);
    av[2] = my_strdup(s3);
    av[3] = NULL;

    return (av);
}

int particular_cases(char *cwd, char **av, shell_t *shell)
{
    char **env = shell->env;

    if (!av[1] || my_strcmp(av[1], "~") == 0) {
        set_env(shell, get_arr("setenv ", "PWD", get_env(env, "HOME")));
        set_env(shell, get_arr("setenv ", "OLDPWD", cwd));
        chdir(get_env(shell->env, "HOME"));
        return (1);
    } else if (my_strcmp(av[1], "-") == 0) {
        set_env(shell, get_arr("setenv ", "PWD", get_env(env, "OLDPWD")));
        set_env(shell, get_arr("setenv ", "OLDPWD", cwd));
        chdir(get_env(env, "PWD"));
        return (1);
    }
    return (0);
}

void cd(shell_t *shell, char **av)
{
    char *path = av[1];
    char *cwd = getcwd(NULL, 0);

    if (particular_cases(cwd, av, shell))
        return;
    if (path[my_strlen(path) - 1] != '/')
        path = my_strcat(path, "/");
    set_env(shell, get_arr("setenv ", "PWD", path));
    set_env(shell, get_arr("setenv ", "OLDPWD", cwd));
    if (chdir(path) == -1) {
        path[my_strlen(path) - 1] = '\0';
        print_error(path, errno, false, true);
        shell->return_value = 1;
    }
}