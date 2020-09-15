/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** minishell header
*/

#ifndef MINISHELL_H_
#define MINISHELL_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct redirection_s
{
    int fd_out;
    int fd_save_out;
    bool twice;
    bool left;
} redirect_t;

typedef struct shell_s
{
    int return_value;
    char **env;
    char *prompt;
    char *input;
    char **arr;
    char ***avs;
    redirect_t redirect;
    bool first_time;
    int pipe_fd[2];
    int mult_pipe_fd[2];
    bool exit;
} shell_t;

#define UNUSED __attribute__((unused))
static const int ERROR = 84;

//MAIN FUNCTIONS
void exec_prog(char **f_av, shell_t *shell);
void cd(shell_t *shell, char **av);
void print_error(char *name, int err, bool more, bool even_more);
void init_shell(shell_t *shell, char **env);

//FORMATTING FUNCTIONS
void format_arr(shell_t *shell);
int only_space_and_tabs(char *str);
int is_multiple_slashes(char *str);
redirect_t get_fd_to_write(shell_t *shell, char **arr);
void close_redirection(shell_t *shell);
int check_for_pipes(shell_t *shell, char **av);

#endif /*MINISHELL_H_*/