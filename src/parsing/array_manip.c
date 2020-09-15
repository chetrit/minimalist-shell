/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** 2d array minipulation function
*/

#include "minishell.h"
#include "my_utils.h"
#include "special_char.h"

int create_single_arr(shell_t *shell, int nb_semicolons)
{
    if (nb_semicolons == 0) {
        shell->avs = malloc(sizeof(char **) * 2);
        shell->avs[0] = shell->arr;
        shell->avs[1] = NULL;
        return (1);
    } else {
        return (0);
    }
}

void create_arrays_extend(shell_t *shell, int *i, int *j)
{
    if (shell->arr[0][0] == ';' && shell->arr[0][1] == '\0') {
            *j += 1;
            *i = 0;
            shell->arr += 1;
        }
    if (is_semicolon(shell->arr[0])) {
        shell->avs[*j][*i] = shell->arr[0];
        *j += 1;
        *i = 0;
        shell->arr += 1;
    }
    shell->avs[*j][(*i)++] = shell->arr[0];
    shell->avs[*j][*i] = NULL;
}

void create_arrays(shell_t *shell)
{
    int nb_semiconlons = get_nb_semicolons(shell);
    int i = 0;
    int j = 0;

    if (create_single_arr(shell, nb_semiconlons))
        return;
    shell->avs = malloc(sizeof(char **) * (nb_semiconlons + 2));
    for (; shell->arr[i]; i++);
    for (j = 0; j < nb_semiconlons + 1; j++) {
        shell->avs[j] = malloc(sizeof(char *) * (i + 1));
    }
    for (i = 0, j = 0; shell->arr[0]; shell->arr++) {
        create_arrays_extend(shell, &i, &j);
    }
    shell->avs[j + 1] = NULL;
    remove_semicolons(shell);
}

void format_arr(shell_t *shell)
{
    char **final = NULL;
    int i = 0;
    int j = 0;

    for (; shell->arr[i]; i++);
    final = malloc(sizeof(char *) * (i + 1));
    for (i = 0, j = 0; shell->arr[i]; i++) {
        if (!only_space_and_tabs(shell->arr[i])) {
            final[j] = my_strdup(shell->arr[i]);
            j += 1;
            final[j] = NULL;
        }
    }
    for (i = 0; final[i]; i++) {
        if (final[i][0] == ' ' || final[i][0] == '\t') {
            final[i] = &final[i][1];
        }
    }
    shell->arr = final;
}