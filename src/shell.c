/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-nathan.cheynet
** File description:
** shell.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "my.h"
#include "error.h"
#include "minishell.h"

void start_minishell(shell_state_t *shell)
{
    char *input = NULL;
    size_t len = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            my_putstr("$> ");
        if (getline(&input, &len, stdin) == -1) {
            my_putstr("\n");
            break;
        }
        if (my_strcmp(input, "exit\n") == 0)
            break;
        if (handle_builtin(shell, input) == FAILURE)
            break;
    }
    free(input);
}
