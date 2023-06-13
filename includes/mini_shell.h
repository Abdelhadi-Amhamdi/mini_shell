/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:13:34 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/13 14:13:12 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include "../parse/parsing.h"
# include "../builtins/builtins.h"
# include "../env/env.h"
# include "../libs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

t_app	*app;

# define HEREDOC_FILENAME "/Users/aamhamdi/tmp/heredoc_file"
 
// pipes
void run_pipeline(t_tree *pipe_node, int out, t_tree *tree);
void run_pipe(t_tree *cmd, int *pipe, int out, int side, t_tree *tree);
void exec_cmd(t_tree *node, t_tree *tree);

// redirection
void run_cmd(t_tree *cmd, int in, int out, t_tree *tree);
void redirection_helper(t_tree *node, int in, int out, t_tree *tree);

int	exec_builtin(t_tree	*cmd, t_env	**env, t_tree *tree);
void executer(t_tree *root, int in, int out, t_tree *tree);

void run_connectors(t_tree *root, int in, int out, t_tree *tree);
char *wildcard(char *condition);

// exec utils
int lexer_list_size(t_lexer *list, int is_b);
char **cmd_args_list_to_tabs(t_tree *node);
char **env_list_to_tabs(t_env *list);
int env_list_size(t_env *list);
char *get_exit_status();
void set_exit_status(int new_status);

// heredoc
void heredoc_handler(t_lexer **root);
t_lexer *heredoc_helper(t_lexer *root);
char *start_heredoc(t_lexer *node, t_boolean to_expand);

void sig_int_handler(int type);
void destroy_ast_tree(t_tree *root);
#endif