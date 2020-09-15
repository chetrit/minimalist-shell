/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** redirections
*/

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "minishell.h"
#include "my_utils.h"

char *get_path_from_redirect(redirect_t *redirect, char **arr)
{
    for (int i = 0; arr[i] != NULL; i++) {
        if (my_strcmp(arr[i], ">") == 0) {
            return (arr[i + 1]);
        }
        if (my_strcmp(arr[i], ">>") == 0) {
            redirect->twice = true;
            return (arr[i + 1]);
        }
        if (my_strcmp(arr[i], "<") == 0) {
            redirect->left = true;
            return (arr[i + 1]);
        }
        if (my_strcmp(arr[i], "<<") == 0) {
            redirect->left = true;
            redirect->twice = true;
            return (arr[i + 1]);
        }
    }
    return (NULL);
}

void delete_redirect(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++) {
        if (my_strcmp(arr[i], ">") == 0) {
            arr[i] = NULL;
            return;
        }
        if (my_strcmp(arr[i], ">>") == 0) {
            arr[i] = NULL;
            return;
        }
        if (my_strcmp(arr[i], "<") == 0) {
            arr[i] = NULL;
            return;
        }
        if (my_strcmp(arr[i], "<<") == 0) {
            arr[i] = NULL;
            return;
        }
    }
}

int check_error_red(char **arr)
{
    int counter = 0;

    for (int i = 0; arr[i] != NULL; i++) {
        if (my_strcmp(arr[i], ">") == 0 || my_strcmp(arr[i], ">>") == 0
            || my_strcmp(arr[i], "<") == 0 || my_strcmp(arr[i], "<<") == 0) {
            counter += 1;
        }
    }
    if (counter <= 2) {
        return (0);
    } else {
        return (1);
    }
}

int redirect_fd(redirect_t *redirect, char *path)
{
    if (!redirect->left) {
        redirect->fd_out = !redirect->twice ?open(path, O_RDWR | O_CREAT |
            O_TRUNC, 0600) : open(path, O_RDWR | O_CREAT | O_APPEND, 0600);
        redirect->fd_save_out = dup(STDOUT_FILENO);
        if (redirect->fd_out == -1 || redirect->fd_save_out == -1
            || dup2(redirect->fd_out, STDOUT_FILENO) == -1) {
            print_error(path, errno, false, true);
            return (1);
        }
    } else {
        redirect->fd_out = open(path, O_RDONLY, 0600);
        redirect->fd_save_out = dup(STDIN_FILENO);
        if (redirect->fd_out == -1 || redirect->fd_save_out == -1
            || dup2(redirect->fd_out, STDIN_FILENO) == -1) {
            print_error(path, errno, false, true);
            return (1);
        }
    }
    return (0);
}

redirect_t get_fd_to_write(shell_t *shell, char **arr)
{
    redirect_t redirect = {-1, -1, false, false};
    char *path = NULL;

    if (check_error_red(arr)) {
        my_put_error("Ambiguous output redirect.\n");
        return (redirect);
    }
    path = get_path_from_redirect(&redirect, arr);
    delete_redirect(arr);
    if (!path) {
        redirect.fd_out = -2;
        return (redirect);
    }
    if (redirect_fd(&redirect, path)) {
        redirect.fd_out = -1;
        shell->return_value = 1;
    }
    return (redirect);
}