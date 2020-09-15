/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** redirections
*/

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

void close_redirection(shell_t *shell)
{
    if (shell->redirect.fd_out > -1) {
        close(shell->redirect.fd_out);
        if (!shell->redirect.left) {
            dup2(shell->redirect.fd_save_out, STDOUT_FILENO);
        } else {
            dup2(shell->redirect.fd_save_out, STDIN_FILENO);
        }
        close(shell->redirect.fd_save_out);
    }
}