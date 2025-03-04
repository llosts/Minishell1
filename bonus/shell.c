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
#include "bonus.h"

void display_prompt(env_node_t *env_list)
{
    char *user = get_env_value(env_list, "USER");
    char *cwd = getcwd(NULL, 0);

    if (!user)
        user = "null";
    if (!cwd)
        cwd = "/";
    my_putstr(TURQUOISE);
    my_putstr(user);
    my_putstr("@minishell" RESET);
    my_putstr(":");
    my_putstr(GREEN);
    my_putstr(cwd);
    my_putstr(BLUE ":$> ");
    free(cwd);
}


void start_minishell(shell_state_t *shell)
{
    char *input = NULL;
    size_t len = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            display_prompt(shell->env_list);
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
