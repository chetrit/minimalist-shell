/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** minishell2 main function
*/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "minishell.h"
#include "my_utils.h"
#include "special_char.h"
#include "env_utils.h"

int parse_null_command(char *str);

void check_commands_one(shell_t *shell, char **av)
{
    if (my_strcmp(av[0], "exit") == 0) {
        shell->return_value = av[1] ? my_atoi(av[1]) : 0;
        shell->exit = true;
        return;
    }
    if (my_strcmp(av[0], "env") == 0)
        return (print_env(shell->env));
    if (my_strcmp(av[0], "setenv") == 0)
        return (set_env(shell, av));
    if (my_strcmp(av[0], "unsetenv") == 0)
        return (unset_env(shell, av));
    if (my_strcmp(av[0], "cd") == 0)
        return (cd(shell, av));
    exec_prog(av, shell);
}

void check_commands(shell_t *shell, char **av)
{
    shell->redirect = get_fd_to_write(shell, av);
    check_commands_one(shell, av);
    close_redirection(shell);
}

void get_input(shell_t *shell)
{
    size_t size = 0;
    int return_value = -1;

    return_value = getline(&shell->input, &size, stdin);
    if (return_value == EOF || return_value == 0 || size == 0) {
        my_putstr("exit\n");
        shell->input = NULL;
        return;
    }
    if (shell->input[return_value - 1] == '\n') {
        shell->input[return_value - 1] = '\0';
    }
}

void loop_arrays(shell_t *shell)
{
    for (int i = 0; shell->avs[i] != NULL; i++) {
        if(check_for_pipes(shell, shell->avs[i])
            || shell->redirect.fd_out == -1) {
            continue;
        }
        check_commands(shell, shell->avs[i]);
    }
    if (shell->exit) {
        exit(shell->return_value);
    }
}

int minishell(shell_t *shell, char **env)
{
    init_shell(shell, env);
    while (1) {
        my_putstr(shell->prompt);
        get_input(shell);
        if (!shell->input) {
            return (shell->return_value);
        }
        shell->return_value = 0;
        if (only_space_and_tabs(shell->input)
            || parse_null_command(shell->input))
            continue;
        shell->input = parse_special_char(shell->input, SPECIAL_CHARS[0]);
        shell->input = parse_special_char(shell->input, SPECIAL_CHARS[1]);
        shell->arr = one_dim_to_two_dim(shell->input, ' ');
        format_arr(shell);
        create_arrays(shell);
        loop_arrays(shell);
        get_prompt(shell);
    }
    return (shell->return_value);
}