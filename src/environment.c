/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-nathan.cheynet
** File description:
** environment.c
*/

#include <stdlib.h>
#include <string.h>

#include "my.h"
#include "minishell.h"

env_node_t *init_env_list(char const **envp)
{
    env_node_t *head = NULL;
    char *key = NULL;
    char *value = NULL;

    for (int i = 0; envp[i] != NULL; i++) {
        key = strtok(my_strdup(envp[i]), "=");
        value = strtok(NULL, "");
        head = add_env_node(head, key, value);
        free(key);
        if (!head) {
            free_env_list(head);
            return NULL;
        }
    }
    return head;
}

env_node_t *add_env_node(env_node_t *head, const char *key, const char *value)
{
    env_node_t *new_node = malloc(sizeof(env_node_t));

    if (!new_node)
        return NULL;
    new_node->key = my_strdup(key);
    new_node->value = my_strdup(value);
    if (!new_node->key || !new_node->value) {
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return NULL;
    }
    new_node->next = head;
    head = new_node;
    return new_node;
}

void free_env_list(env_node_t *head)
{
    env_node_t *tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}
