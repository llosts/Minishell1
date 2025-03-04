/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-nathan.cheynet
** File description:
** main.c
*/

#include <stdlib.h>

#include "my.h"
#include "error.h"
#include "minishell.h"

int main(int argc, char const **argv, char const **envp)
{
    shell_state_t shell;

    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        display_help();
        return SUCCESS;
    }
    if (argc != 1 || envp == NULL)
        print_error("Error: Invalid arguments\n", FAILURE);
    shell.env_list = init_env_list(envp);
    shell.last_exit_status = 0;
    start_minishell(&shell);
    free_env_list(shell.env_list);
    return shell.last_exit_status;
}
