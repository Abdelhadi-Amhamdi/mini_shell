/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:13:34 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/09 18:55:28 by aamhamdi         ###   ########.fr       */
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
# define HEREDOC_FILENAME "heredoc_file"
 
// pipes
int run_pipeline(t_tree *pipe_node, int out);
void run_pipe(t_tree *cmd, int *pipe, int out, int side);
void exec_cmd(t_tree *node);

// redirection
int run_cmd(t_tree *cmd, int in, int out);
int run_rdir(t_tree *node, int out);
int redirection_helper(t_tree *node, int in, int out);

int	exec_builtin(t_tree	*cmd, t_env	**env);
int executer(t_tree *root, int in, int out);

int run_connectors(t_tree *root, int in, int out);
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
#endif