/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-nathan.cheynet
** File description:
** builtins.c
*/

#include <stdlib.h>

#include "my.h"
#include "error.h"
#include "minishell.h"

static const builtin_t builtin_handler[] = {
    {"cd", &my_cd},
    {"setenv", &my_setenv},
    {"unsetenv", &my_unsetenv},
    {"env", &my_env},
    {NULL, NULL}
};

static int handle_error_setenv(char **args)
{
    int index = 1;

    if (args[2] != NULL && args[3] != NULL)
        return print_error("setenv: Too many arguments.\n", 1);
    if (args[1][0] != '_' && my_isalpha(args[1][0]) == 0)
        return print_error("setenv: Variable name must begin with a letter.\n",
            1);
    while (args[1][index] != '\0') {
        if (my_isalnum(args[1][index]) == 0 && args[1][index] != '.' &&
            args[1][index] != '_')
            return print_error("setenv: Variable name must contain "
                "alphanumeric characters.\n", 1);
        index += 1;
    }
    return 0;
}

static void helper_unsetenv(env_node_t *current, env_node_t **prev,
    env_node_t **head)
{
    if (*prev == NULL)
        *head = current->next;
    else
        (*prev)->next = current->next;
    free(current->key);
    free(current->value);
    free(current);
}

int my_cd(shell_state_t *shell, char **args)
{
    char *target_dir = NULL;
    int ret = 0;

    if (args[1] != NULL && args[2] != NULL)
        return print_error("cd: Too many arguments.\n", 1);
    target_dir = get_target_directory(shell, args);
    if (!target_dir)
        return 1;
    ret = change_directory(shell, target_dir);
    return ret;
}

int my_setenv(shell_state_t *shell, char **args)
{
    env_node_t *current = shell->env_list;

    if (!args[1])
        return my_env(shell, args);
    if (handle_error_setenv(args) == 1)
        return 1;
    while (current != NULL) {
        if (my_strcmp(args[1], current->key) == 0) {
            free(current->value);
            current->value = my_strdup(args[2] != NULL ? args[2] : "");
            return SUCCESS;
        }
        current = current->next;
    }
    shell->env_list = add_env_node(shell->env_list, args[1],
        args[2] != NULL ? args[2] : "");
    if (shell->env_list == NULL)
        return FAILURE;
    return SUCCESS;
}

int my_unsetenv(shell_state_t *shell, char **args)
{
    env_node_t *current = shell->env_list;
    env_node_t *prev = NULL;

    if (!args[1])
        return print_error("unsetenv: Too few arguments.\n", 1);
    while (current != NULL) {
        if (my_strcmp(current->key, args[1]) == 0) {
            helper_unsetenv(current, &prev, &shell->env_list);
            break;
        }
        prev = current;
        current = current->next;
    }
    if (args[2] != NULL)
        return my_unsetenv(shell, &args[1]);
    return SUCCESS;
}

int my_env(shell_state_t *shell, char **args)
{
    env_node_t *reversed_list = create_reversed_copy(shell->env_list);
    env_node_t *current = NULL;

    (void)args;
    if (reversed_list == NULL)
        return FAILURE;
    current = reversed_list;
    while (current != NULL) {
        my_putstr(current->key);
        my_putstr("=");
        my_putstr(current->value);
        my_putstr("\n");
        current = current->next;
    }
    free_env_list(reversed_list);
    return SUCCESS;
}

int handle_builtin(shell_state_t *shell, char *input)
{
    int index = 0;
    char **args = parse_input(input);

    if (args[0] == NULL)
        return SUCCESS;
    while (builtin_handler[index].name != NULL) {
        if (my_strcmp(args[0], builtin_handler[index].name) == 0) {
            shell->last_exit_status = builtin_handler[index].func(shell, args);
            free_array(args);
            return SUCCESS;
        }
        index++;
    }
    shell->last_exit_status = execute_command(shell, args);
    free_array(args);
    return SUCCESS;
}
