/*
** EPITECH PROJECT, 2019
** one_dim_to_two_dim
** File description:
** one_dim_to_two_dim
*/

#include <stdlib.h>

int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);

int is_multiple_slashes(char *str)
{
    int counter = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '/')
            counter += 1;
    if (counter != 1)
        return (1);
    return (0);
}

int only_space_and_tabs(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ' && str[i] != '\t')
            return (0);
    return (1);
}

int get_nb_separators(char *str, char separator)
{
    int counter = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == separator || str[i] == '\t')
            counter += 1;
    return (counter);
}

char **one_dim_to_two_dim(char *str, char delim)
{
    char **arr = malloc(sizeof(char *) * (get_nb_separators(str, delim) + 2));
    int i = 0;
    int j = 0;

    for (; str[j] != '\0'; j++)
        if (str[j] == delim || str[j] == '\t') {
            arr[i] = malloc(sizeof(char) * (j + 1));
            arr[i] = my_strncpy(arr[i], str, j);
            arr[i][j] = '\0';
            str += j + 1;
            j = 0;
            i += 1;
        }
    arr[i] = malloc(sizeof(char) * (my_strlen(str) + 1));
    arr[i][j] = '\0';
    arr[i] = my_strcpy(arr[i], str);
    arr[i + 1] = NULL;
    return (arr);
}