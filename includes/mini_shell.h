/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:13:34 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/16 11:21:39 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include "../parse/parsing.h"
# include "../builtins/builtins.h"
# include "../env/env.h"
# include "../libs/libft/libft.h"
# include "../libs/gnl/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

int	g_exit_status;

# define HEREDOC_FILENAME "/tmp/heredoc_file"

// pipes
void	run_pipeline(t_tree *pipe_node, int out, t_main *data);
void	run_pipe(t_tree *cmd, int *pipe, int out, int side, t_main *data);
void	exec_cmd(t_tree *node, t_main *data);

// redirection
void	run_cmd(t_tree *cmd, int in, int out, t_main *data);
void	redirection_helper(t_tree *node, int in, int out, t_main *data);

int		exec_builtin(t_tree	*cmd, t_env	**env, t_main *data, int out);
void	executer(t_tree *root, int in, int out, t_main *data);

void	run_connectors(t_tree *root, int in, int out, t_main *data);
char	*wildcard(char *condition);

// exec utils
int		lexer_list_size(t_lexer *list, int is_b);
char	**cmd_args_list_to_tabs(t_tree *node, t_main *data);
char	**env_list_to_tabs(t_env *list);
int		env_list_size(t_env *list);

// heredoc
void	heredoc_handler(t_lexer **root);
t_lexer	*heredoc_helper(t_lexer *root);
char	*start_heredoc(t_lexer *node, t_boolean to_expand, t_main *data);

void	sig_int_handler(int type);
void	destroy_ast_tree(t_tree *root);
#endif