/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** execute
*/

#include "execute.h"

void exit_print(int status, shell_t *shell)
{
    if (WIFEXITED(status))
        return;
    if (WIFSIGNALED(status)) {
        my_put_error(signals[WTERMSIG(status)]);
        #ifdef WCOREDUMP
        if (WCOREDUMP(status)) {
            my_put_error(" (core dumped)");
        }
        #endif
        my_put_error("\n");
    }
    shell->return_value = status;
}

int exec_my_prog(char **av, char *path, shell_t *shell)
{
    int status = 0;
    pid_t id = fork();

    if (av[0][0] == '.' && av[0][1] == '/')
        av[0] += 2;
    if (id == - 1) {
        return (-1);
    } else if (id == 0) {
        if (execve(path, av, shell->env) == -1) {
            if (errno == ENOEXEC) {
                my_putstr(EREXEC(path));
                exit(0);
            }
            return (-1);
        }
    } else {
        waitpid(id, &status, 0);
        exit_print(status, shell);
    }
    return (0);
}

void check_to_exec(char **path_arr, char **av, shell_t *shell)
{
    char *path = NULL;
    char *name = my_strdup(av[0]);

    for (int i = 0; path_arr[i] != NULL; i++) {
        path = malloc(sizeof(char) *
            (my_strlen(path_arr[i]) + my_strlen(name + 1)));
        path = path_arr[i];
        path = path_arr[i][my_strlen(path_arr[i]) - 1] == '/' ?
            my_strcat(path, name) : my_strcat(my_strcat(path, "/"), name);
        if (access(path, X_OK) != -1 && exec_my_prog(av, path, shell) != -1) {
            return;
        }
    }
    shell->return_value = 1;
    access(path, X_OK) == -1 ? my_put_error(my_strcat(my_strcat(name, ":"),
        " Command not found.\n")) : print_error(name, errno, false, false);
}

int search_path(char **av, shell_t *shell)
{
    char *path = NULL;
    char **path_arr = NULL;
    char *name = my_strdup(av[0]);

    if (av[0][0] == '/') {
        if (exec_my_prog(av, av[0], shell) == -1)
            print_error(name, errno, false, true);
        return (0);
    }
    path = get_env(shell->env, "PATH");
    if (!path) {
        path = "/bin:/usr/bin:/usr/local/bin";
    }
    path_arr = one_dim_to_two_dim(path, ':');
    check_to_exec(path_arr, av, shell);
    return (0);
}

void exec_prog(char **av, shell_t *shell)
{
    char *cwd = getcwd(NULL, 0);

    if (my_strcmp(cwd, "/") == 0 && access(av[0], X_OK) != -1) {
        av[0] = my_strcat("/", av[0]);
    }
    if ((av[0][0] == '.' && av[0][1] == '/') || av[0][0] == '/'|| access(
            my_strcat(my_strcat(getcwd(NULL, 0), "/"), av[0]), X_OK) == 0) {
        if (access(av[0], X_OK) == -1 || exec_my_prog(av, av[0], shell) == -1) {
            return (print_error(av[0], errno, av[0][0] == '/' ? 0 : 1, true));
        }
    } else {
        search_path(av, shell);
    }
}
