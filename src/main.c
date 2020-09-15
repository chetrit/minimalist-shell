/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** main
*/

#include "minishell.h"
#include "my_utils.h"

int minishell(shell_t *shell, char **envp);

int main(UNUSED int ac, UNUSED char **av, char **envp)
{
    shell_t shell;

    return (minishell(&shell, envp));
}