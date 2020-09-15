/*
** EPITECH PROJECT, 2019
** my_strdup
** File description:
** allocates memory and copies the string given as argument in it
*/

#include <stdlib.h>

int my_strlen(char const *src);

char *my_strdup(char const *src)
{
    char *str = malloc(sizeof(char) * (my_strlen(src) + 1));
    int i = 0;

    for (; i < my_strlen(src); i++) {
        str[i] = src[i];
    }
    str[i] = '\0';
    return (str);
}
