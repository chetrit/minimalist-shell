/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** prompt
*/

#include <unistd.h>
#include "minishell.h"
#include "my_utils.h"
#include "env_utils.h"

char *get_last_slash(char *path)
{
    char *ptr = path;

    if (my_strcmp(path, "/") == 0)
        return (path);
    for (int i = 0; path[i] != '\0'; i++)
        if (path[i] == '/')
            ptr = &path[i + 1];
    return (ptr);
}

void get_prompt(shell_t *shell)
{
    char *user = get_env(shell->env, "USER");
    char *hostname = get_env(shell->env, "HOSTNAME");
    char *pwd = get_last_slash(getcwd(NULL, 0));
    int i = 0;

    if (!user || !hostname || !pwd) {
        shell->prompt = "$>";
        return;
    }
    for (; hostname[i] != '\0' && hostname[i] != '.'; i++);
    hostname[i] = '\0';
    shell->prompt = malloc(sizeof(char) * (
        my_strlen(user) + my_strlen(hostname) + my_strlen(pwd) +1));
    shell->prompt = my_strcat(my_strcat("{", my_strcat(my_strcat(
        my_strcat(my_strcat(user, "@"), hostname), " "), pwd)), "}$ ");
}