/*
** EPITECH PROJECT, 2020
** minishell2
** File description:
** pipes
*/

#include <unistd.h>

#include "minishell.h"
#include "my_utils.h"
#include "pipes.h"

int get_nb_after_pipe(char **arr)
{
    int i = 0;

    for (; arr[i] && my_strcmp(arr[i], "|") != 0; i++);
    return (i + 1);
}

char **get_next_command(char **av)
{
    char **tmp_av = NULL;
    int i = 0;
    int j = 0;

    for (i = 0; av[i] && my_strcmp(av[i], "|") != 0; i++);
    if (!av[i]) {
        return (NULL);
    }
    tmp_av = malloc(sizeof(char *) * (get_nb_after_pipe(&av[++i])));
    for (j = 0; av[i] && my_strcmp(av[i], "|") != 0; i++, j++) {
        tmp_av[j] = my_strdup(av[i]);
    }
    tmp_av[j] = NULL;
    return (tmp_av);
}