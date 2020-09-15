/*
** EPITECH PROJECT, 2020
** minishell
** File description:
** shell init
*/

#include "minishell.h"
#include "env_utils.h"

void init_shell(shell_t *shell, char **env)
{
    shell->input = NULL;
    shell->return_value = 0;
    shell->first_time = true;
    shell->redirect = (redirect_t) {0, 0, 0, 0};
    shell->pipe_fd[0] = -1;
    shell->pipe_fd[1] = -1;
    shell->mult_pipe_fd[0] = -1;
    shell->mult_pipe_fd[1] = -1;
    shell->exit = false;
    cp_env(shell, env);
    get_prompt(shell);
}