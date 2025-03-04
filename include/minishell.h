/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-nathan.cheynet
** File description:
** minishell.h
*/

#ifndef MINISHELL_H_
    #define MINISHELL_H_

typedef struct env_node_s {
    char *key;
    char *value;
    struct env_node_s *next;
} env_node_t;

typedef struct shell_state_s {
    env_node_t *env_list;
    int last_exit_status;
} shell_state_t;

typedef struct builtin_s {
    char *name;
    int (*func)(shell_state_t *shell, char **args);
} builtin_t;

env_node_t *init_env_list(char const **envp);
env_node_t *add_env_node(env_node_t *head, const char *key, const char *value);
void free_env_list(env_node_t *head);

void start_minishell(shell_state_t *shell);
int handle_builtin(shell_state_t *shell, char *input);

int my_cd(shell_state_t *shell, char **args);
int my_setenv(shell_state_t *shell, char **args);
int my_unsetenv(shell_state_t *shell, char **args);
int my_env(shell_state_t *shell, char **args);

env_node_t *create_reversed_copy(env_node_t *head);
char **convert_env_list_to_array(env_node_t *env_list);
char **resize_array(char **old_array, int old_size, int new_size);
char **parse_input(char *input);
void free_array(char **array);

int change_directory(shell_state_t *shell, const char *target_dir);
char *expand_home(shell_state_t *shell, const char *path);
char *get_target_directory(shell_state_t *shell, char **args);
char *get_env_value(env_node_t *env_list, const char *key);

int execute_command(shell_state_t *shell, char **args);
int fork_and_execute(char *cmd_path, char **args, shell_state_t *shell);
void execute_child_process(char *cmd_path, char **args, shell_state_t *shell);
char *get_command_path(shell_state_t *shell, char **args);
char *find_command_in_path(shell_state_t *shell, const char *command);

#endif
