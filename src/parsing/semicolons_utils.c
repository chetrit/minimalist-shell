/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** semicolons utils for parsing
*/

#include "minishell.h"
#include "my_utils.h"

bool is_semicolon(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ';') {
            return (true);
        }
    }
    return (false);
}

char *delete_semicolon(char *str)
{
    if (!is_semicolon(str)) {
        return (str);
    } else if (str[0] == ';') {
        return (&str[1]);
    } else {
        str[my_strlen(str) - 1] = '\0';
        return (str);
    }
}

void remove_semicolons(shell_t *shell)
{
    for (int i = 0; shell->avs[i]; i++) {
        for (int j = 0; shell->avs[i][j]; j++) {
            shell->avs[i][j] = delete_semicolon(shell->avs[i][j]);
        }
    }
}

int get_nb_semicolons(shell_t *shell)
{
    int nb = 0;

    for (int i = 0; shell->arr[i] != NULL; i++) {
        for (int j = 0; shell->arr[i][j] != '\0'; j++) {
            nb = shell->arr[i][j] == ';' ? nb + 1 : nb;
        }
    }
    return (nb);
}