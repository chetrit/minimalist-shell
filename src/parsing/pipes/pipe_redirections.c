/*
** EPITECH PROJECT, 2020
** minishell
** File description:
** pipes redirections
*/

#include <unistd.h>

#include "minishell.h"
#include "pipes.h"

void redirect_output(shell_t *shell, char **tmp_av)
{
    int save_fd = dup(STDOUT_FILENO);

    dup2(shell->pipe_fd[1], STDOUT_FILENO);
    check_commands(shell, tmp_av);
    dup2(save_fd, STDOUT_FILENO);
    close(save_fd);
    close(shell->pipe_fd[1]);
}

void redirect_input(shell_t *shell, char **tmp_av, int pipe_fd[2])
{
    int save_fd = dup(STDIN_FILENO);

    dup2(pipe_fd[0], STDIN_FILENO);
    check_commands(shell, tmp_av);
    dup2(save_fd, STDIN_FILENO);
    close(save_fd);
    close(pipe_fd[0]);
}

void redirect_input_and_output_even(shell_t *shell, char **tmp_av)
{
    int save_in = dup(STDIN_FILENO);
    int save_out = dup(STDOUT_FILENO);

    dup2(shell->pipe_fd[0], STDIN_FILENO);
    dup2(shell->mult_pipe_fd[1], STDOUT_FILENO);
    check_commands(shell, tmp_av);
    dup2(save_in, STDIN_FILENO);
    dup2(save_out, STDOUT_FILENO);
    close(save_in);
    close(save_out);
    close(shell->mult_pipe_fd[1]);
    close(shell->pipe_fd[0]);
    pipe(shell->pipe_fd);
}

void redirect_input_and_output_odd(shell_t *shell, char **tmp_av)
{
    int save_in = dup(STDIN_FILENO);
    int save_out = dup(STDOUT_FILENO);

    dup2(shell->mult_pipe_fd[0], STDIN_FILENO);
    dup2(shell->pipe_fd[1], STDOUT_FILENO);
    check_commands(shell, tmp_av);
    dup2(save_in, STDIN_FILENO);
    dup2(save_out, STDOUT_FILENO);
    close(save_in);
    close(save_out);
    close(shell->pipe_fd[1]);
    close(shell->mult_pipe_fd[0]);
    pipe(shell->mult_pipe_fd);
}