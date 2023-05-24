/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:13:34 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/24 14:53:46 by aamhamdi         ###   ########.fr       */
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
void run_pipeline(t_tree *pipe_node, int in, int out);
void run_pipe(t_tree *cmd, int *pipe,int in, int out, int side);
void exec_cmd(t_tree *node, int p1, int p2, int std, int old);

// redirection
void run_cmd(t_tree *cmd, t_env *env);
void run_rdir(t_tree *node);

void	exec_builtin(t_tree	*cmd, t_env	*env);
#endif