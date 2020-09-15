/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** environnement utils header
*/

#ifndef ENV_UTILS_H_
#define ENV_UTILS_H_

void set_env(shell_t *shell, char **av);
void unset_env(shell_t *shell, char **av);

char *get_env(char **envp, char *str);
void cp_env(shell_t *shell, char **env);

void print_env(char **envp);

void get_prompt(shell_t *shell);

typedef struct list_s
{
    char *str;
    struct list_s *next;
} list_t;

#endif /*ENV_UTILS_H_*/