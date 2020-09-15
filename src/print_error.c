/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** print error function
*/

#include <stdbool.h>
#include <string.h>
#include "my_utils.h"

void print_error(char *name, int err, bool more, bool even_more)
{
    if (more) {
        my_put_error("./");
    }
    my_put_error(name);
    my_put_error(": ");
    if (!even_more) {
        my_put_error(my_strcat(strerror(err), "\n"));
    } else {
        my_put_error(my_strcat(my_strcat(strerror(err), "."), "\n"));
    }
}