/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-nathan.cheynet
** File description:
** my_cd.c
*/

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "my.h"
#include "error.h"
#include "minishell.h"

static int manage_cd_error(const char *target)
{
    print_error(target, 1);
    if (errno == EACCES)
        return print_error(": Permission denied.\n", 1);
    if (errno == ENOENT)
        return print_error(": No such file or directory.\n", 1);
    return print_error(": Not a directory.\n", 1);
}

static int is_valid_user(const char *path)
{
    if (path[1] != '/' && path[1] != '\0') {
        print_error("Unknown user: ", 1);
        print_error(&path[1], 1);
        print_error(".\n", 1);
        return 1;
    }
    return 0;
}

char *expand_home(shell_state_t *shell, const char *path)
{
    char *home = get_env_value(shell->env_list, "HOME");
    char *expanded_path = NULL;

    if (!home) {
        write(STDERR_FILENO, "cd: HOME not set.\n", 18);
        return NULL;
    }
    if (is_valid_user(path) != 0)
        return NULL;
    expanded_path = malloc(sizeof(char) * (my_strlen(home) + my_strlen(path)));
    if (!expanded_path)
        return NULL;
    my_strcpy(expanded_path, home);
    my_strcat(expanded_path, path + 1);
    return expanded_path;
}

char *get_target_directory(shell_state_t *shell, char **args)
{
    char *oldpwd = NULL;

    if (!args[1] || my_strcmp(args[1], "~") == 0)
        return get_env_value(shell->env_list, "HOME");
    if (args[1][0] == '~')
        return expand_home(shell, args[1]);
    if (my_strcmp(args[1], "-") == 0) {
        oldpwd = get_env_value(shell->env_list, "OLDPWD");
        if (oldpwd == NULL)
            return NULL;
        my_putstr(oldpwd);
        my_putstr("\n");
        return oldpwd;
    }
    return args[1];
}

int change_directory(shell_state_t *shell, const char *target)
{
    char *oldpwd = getcwd(NULL, 0);
    char *newpwd = NULL;

    if (!oldpwd)
        return 1;
    if (chdir(target) != 0) {
        free(oldpwd);
        return manage_cd_error(target);
    }
    my_setenv(shell, (char *[]) {"setenv", "OLDPWD", oldpwd, NULL});
    free(oldpwd);
    newpwd = getcwd(NULL, 0);
    if (newpwd) {
        my_setenv(shell, (char *[]) {"setenv", "PWD", newpwd, NULL});
        free(newpwd);
    }
    return 0;
}

char *get_env_value(env_node_t *env_list, const char *key)
{
    while (env_list != NULL) {
        if (my_strcmp(env_list->key, key) == 0)
            return env_list->value;
        env_list = env_list->next;
    }
    return NULL;
}
