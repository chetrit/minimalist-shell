/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** env related functions
*/

#include <unistd.h>
#include <sys/stat.h>
#include "minishell.h"
#include "my_utils.h"

void print_env(char **envp)
{
    if (!envp)
        return;
    for (int i = 0; envp[i] != NULL; i++)
        my_putstr(my_strcat(envp[i], "\n"));
}

char *get_env(char **envp, char *str)
{
    char *line = NULL;
    bool cond = false;

    if (!envp)
        return (NULL);
    for (int i = 0; envp[i] != NULL; i++) {
        if (my_strncmp(str, envp[i], my_strlen(str)) == 0) {
            line = envp[i];
            cond = true;
            break;
        }
    }
    if (!cond)
        return (NULL);
    if (line[1])
        while ((line++)[0] != '=');
    return (line);
}

char *create_variable(char **env, char *variable, char *default_str)
{
    char *str = NULL;

    if (!get_env(env, variable))
        str = default_str;
    else {
        str = malloc(sizeof(char) * (my_strlen(get_env(env, variable) + 1)));
        str = my_strcat(my_strcat(variable, "="), get_env(env, variable));
    }
    return (str);
}

void create_env(shell_t *shell, char **old_env)
{
    char **env;
    char *cpath = getcwd(NULL, 0);
    int i = 0;

    for (; old_env && old_env[i] != NULL; i++);
    env = malloc(sizeof(char *) * (i + 6));
    for (i = 0; old_env && old_env[i] != NULL; i++)
        env[i] = my_strdup(old_env[i]);
    env[i++] = "VENDOR=unknown";
    env[i++] = my_strcat("PWD=", cpath);
    env[i++] = create_variable(old_env, "HOST", "HOST=localhost.localdomain");
    env[i++] = create_variable(
        old_env, "PATH", "PATH=/bin:/usr/bin:/usr/local/bin");
    env[i++] = create_variable(old_env, "USER", "USER=unknown");
    env[i++] = NULL;
    shell->env = env;
}

void cp_env(shell_t *shell, char **env)
{
    int i;
    int j;

    if (!get_env(env, "USER") || !get_env(env, "PATH")
        || !get_env(env, "PWD") || !get_env(env, "HOST")) {
        create_env(shell, env);
        return;
    }
    for (i = 0; env[i] != NULL; i++);
    shell->env = malloc(sizeof(char *) * (i + 2));
    for (j = 0; env[j] != NULL; j++) {
        shell->env[j] = malloc(sizeof(char) * (my_strlen(env[j]) + 1));
        shell->env[j] = my_strcpy(shell->env[j], env[j]);
    }
    shell->env[j] = NULL;
}
