/*
** EPITECH PROJECT, 2020
** minishell
** File description:
** null command parser
*/

#include "my_utils.h"

int nb_sc(char *str, char c);

int is_null_command(char *str)
{
    int counter = 0;
    int i = 0;

    for (; str[i] != '|'; i++) {
        if (is_alphanum(str[i])) {
            counter++;
        }
    }
    if (counter == 0) {
        return (1);
    }
    for (counter = 0; str[i] != '\0'; i++) {
        if (is_alphanum(str[i])) {
            return (0);
        }
    }
    return (1);
}

int parse_null_command(char *str)
{
    if (nb_sc(str, '|') > 0 && is_null_command(str)) {
        my_put_error("Invalid null command.\n");
        return (1);
    }
    return (0);
}