/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:13:34 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/05 14:33:43 by aamhamdi         ###   ########.fr       */
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


// pipes
int run_pipeline(t_tree *pipe_node, int in, int out);
void run_pipe(t_tree *cmd, int *pipe,int in, int out, int side);
void exec_cmd(t_tree *node, int p1, int p2, int std, int old);

// redirection
int run_cmd(t_tree *cmd, t_env **env);
int run_rdir(t_tree *node);

int	exec_builtin(t_tree	*cmd, t_env	**env);
int	herdoc(t_tree *hrd, t_app *app);
int executer(t_tree *root, t_app *app);

int run_connectors(t_tree *root, t_app *app);
char *wildcard(char *condition);

// exec utils
int lexer_list_size(t_lexer *list);
char **cmd_args_list_to_tabs(t_tree *node, t_env **env);
char **env_list_to_tabs(t_env *list);
int env_list_size(t_env *list);

#endif