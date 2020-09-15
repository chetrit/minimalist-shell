/*
** EPITECH PROJECT, 2020
** minishell2
** File description:
** pipes
*/

#include <unistd.h>
#include <sys/wait.h>

#include "minishell.h"
#include "my_utils.h"
#include "pipes.h"

char **get_first_command(char **av)
{
    char **tmp_av = NULL;
    int i = 0;

    for (i = 0; av[i] && my_strcmp(av[i], "|") != 0; i++);
    tmp_av = malloc(sizeof(char *) * (i + 1));
    for (i = 0; av[i] && my_strcmp(av[i], "|") != 0; i++)
        tmp_av[i] = my_strdup(av[i]);
    tmp_av[i] = NULL;
    return (tmp_av);
}

char **get_last_command(char **av)
{
    char **last = NULL;
    int j = 0;
    int stock = 0;
    int nb = 0;

    for (int i = 0; av[i]; i++) {
        j = my_strcmp(av[i], "|") == 0 ? i : j;
    }
    stock = j;
    for (; av[j]; j++, nb++);
    last = malloc(sizeof(char *) * (nb + 1));
    nb = stock;
    for (j = 0, ++stock; av[stock]; stock++, j++) {
        last[j] = my_strdup(av[stock]);
    }
    last[j] = NULL;
    av[nb] = NULL;
    return (last);
}

void apply_pipe(shell_t *shell, char **av)
{
    char **tmp_av = NULL;
    char **last = get_last_command(av);
    int i = 0;

    tmp_av = get_first_command(av);
    pipe(shell->pipe_fd);
    redirect_output(shell, tmp_av);
    if (!get_next_command(av)) {
        return (redirect_input(shell, last, shell->pipe_fd));
    }
    for (pipe(shell->mult_pipe_fd); av && tmp_av; ++i) {
        tmp_av = get_next_command(av);
        if (!tmp_av)
            break;
        av += get_nb_after_pipe(av);
        i % 2 == 0 ? redirect_input_and_output_even(shell, tmp_av) :
            redirect_input_and_output_odd(shell, tmp_av);
    }
    i % 2 == 0 ? redirect_input(shell, last, shell->pipe_fd) :
        redirect_input(shell, last, shell->mult_pipe_fd);
}

void apply_single_pipe(shell_t *shell, char **av)
{
    pid_t id = fork();
    int status = 0;

    if (id == -1)
        return;
    if (id == 0) {
        redirect_output_single(shell, get_first_command(av));
        exit(0);
    } else {
        redirect_input_single(shell, get_last_command(av), shell->pipe_fd);
        waitpid(id, &status, 0);
    }
}

int check_for_pipes(shell_t *shell, char **av)
{
    unsigned int nb_pipes = 0;

    for (int i = 0; av[i] != NULL; i++) {
        if (my_strcmp(av[i], "|") == 0) {
            nb_pipes++;
        }
    }
    if (nb_pipes == 0 || nb_pipes > 9) {
        return (0);
    }
    if (nb_pipes == 1) {
        pipe(shell->pipe_fd);
        if (my_strcmp(av[0],  "exit") == 0)
            shell->return_value = av[1] ? my_atoi(av[1]) : 0;
        apply_single_pipe(shell, av);
        return (1);
    } else {
        apply_pipe(shell, av);
        return (1);
    }
}
