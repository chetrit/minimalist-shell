/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** pipes header
*/

#ifndef PIPES_H_
#define PIPES_H_

void check_commands(shell_t *shell, char **av);
char **get_next_command(char **av);
void redirect_output(shell_t *shell, char **tmp_av);
void redirect_input(shell_t *shell, char **tmp_av, int pipe_fd[2]);
void redirect_input_and_output_odd(shell_t *shell, char **tmp_av);
void redirect_input_and_output_even(shell_t *shell, char **tmp_av);
void redirect_output_single(shell_t *shell, char **tmp_av);
void redirect_input_single(shell_t *shell, char **tmp_av, int pipe_fd[2]);
int get_nb_after_pipe(char **arr);

#endif /*PIPES_H_*/