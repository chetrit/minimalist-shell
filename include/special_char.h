/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** semicolons header
*/

#ifndef SEMICOLONS_H_
#define SEMICOLONS_H_

bool is_semicolon(char *str);
int get_nb_semicolons(shell_t *shell);
void remove_semicolons(shell_t *shell);
char *parse_special_char(char *input, char c);
void create_arrays(shell_t *shell);

static char const SPECIAL_CHARS[2] = {';', '|'};
#endif /*SEMICOLONS_H_*/