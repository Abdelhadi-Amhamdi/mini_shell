/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:22 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/12 21:17:51 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void exec_cmd(t_tree *node, t_tree *tree)
{
	int status ;
	if (node->is_builtin)
	{
		status = exec_builtin(node, &app->env_list, tree);
		exit (status);
	}
	else
		execve(node->args[0], node->args, NULL);
}

void run_pipe(t_tree *cmd, int *pipe, int out, int side, t_tree *tree)
{
	int		std_file;
	int		used_end;
	int		unused_end;
	
	used_end = pipe[PIPE_READ_END];
	unused_end = pipe[PIPE_WRITE_END];
	std_file = STDIN_FILENO;
	if (side == LEFT_CHILD)
	{
		used_end = pipe[PIPE_WRITE_END];
		unused_end = pipe[PIPE_READ_END];
		std_file = STDOUT_FILENO;
	}
	if (cmd->type == CMD)
	{
		cmd->args = cmd_args_list_to_tabs(cmd);
		cmd->id = fork();
		if (!cmd->id)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			close(unused_end);
			dup2(used_end, std_file);
			close(used_end);
			dup2(out, STDOUT_FILENO);
			if (out != STDOUT_FILENO && out != -1)
				close(out);
			exec_cmd(cmd, tree);	
		}
		ft_free(cmd->args);
	}
	else
		executer(cmd, STDIN_FILENO, used_end, tree);
}

void run_pipeline(t_tree *pipe_node, int out, t_tree *tree)
{
	int fds[2];

	pipe(fds);
	run_pipe(pipe_node->left, fds, -1, LEFT_CHILD, tree);
	run_pipe(pipe_node->right, fds, out, RIGHT_CHILD, tree);
	if (out != STDOUT_FILENO)
		close(out);
	close(fds[PIPE_WRITE_END]);
	close(fds[PIPE_READ_END]);
}
