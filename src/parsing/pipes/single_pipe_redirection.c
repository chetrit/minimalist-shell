/*
** EPITECH PROJECT, 2020
** minishell
** File description:
** simple pipes redirections
*/

#include <unistd.h>

#include "minishell.h"
#include "pipes.h"

void redirect_output_single(shell_t *shell, char **tmp_av)
{
    int save_fd = dup(STDOUT_FILENO);

    close(shell->pipe_fd[0]);
    dup2(shell->pipe_fd[1], STDOUT_FILENO);
    check_commands(shell, tmp_av);
    dup2(save_fd, STDOUT_FILENO);
    close(save_fd);
    close(shell->pipe_fd[1]);
}

void redirect_input_single(shell_t *shell, char **tmp_av, int pipe_fd[2])
{
    int save_fd = dup(STDIN_FILENO);

    close(shell->pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    check_commands(shell, tmp_av);
    dup2(save_fd, STDIN_FILENO);
    close(save_fd);
    close(pipe_fd[0]);
}