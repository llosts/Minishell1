/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-nathan.cheynet
** File description:
** usage.c
*/

#include <unistd.h>

#include "my.h"

void display_help(void)
{
    my_putstr("USAGE\n");
    my_putstr("    ./mysh\n\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("    mysh is a simple shell that can run ");
    my_putstr("commands and manage environment variables.\n");
}

int print_error(const char *message, int return_value)
{
    write(STDERR_FILENO, message, my_strlen(message));
    return return_value;
}
