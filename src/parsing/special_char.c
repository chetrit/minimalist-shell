/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** special_char parser
*/

#include "minishell.h"
#include "my_utils.h"

int is_alphanum(char const c)
{
    if ((c < 48 || c > 57) && (c < 'a' || c > 'z') && (c < 'A' || c > 'Z'))
        return 0;
    return 1;
}

int nb_sc(char *str, char c)
{
    int counter = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            counter += 1;
        }
    }
    return (counter);
}

char *clean_special_char(char *str, char c)
{
    char *cpy = malloc(sizeof(char) * (my_strlen(str) + nb_sc(str, c) * 3 + 1));
    bool cond = false;
    int j = 0;

    for (int i = 0; i < my_strlen(str); i++) {
        if (str[i] == c && cond == false) {
            cond = true;
            cpy[j] = ' ';
            cpy[j + 1] = c;
            cpy[j + 2] = ' ';
            j += 3;
            i += 1;
        }
        for (; (str[i] == ' ' || str[i] == c || str[i] == '\t') && cond; i++);
        cond = false;
        if (str[i] != c)
            cpy[j++] = str[i];
    }
    cpy[j] = '\0';
    return (cpy);
}

char *parse_special_char(char *input, char c)
{
    int i = 0;

    if (nb_sc(input, c) == 0)
        return (input);
    input = clean_special_char(input, c);
    for (i = my_strlen(input) - 1;
        input[i] != c && (input[i] == ' ' || input[i] == '\t'); i--);
    for (; input[i] == c; i--) {
        input[i] = '\0';
    }
    return (input);
}