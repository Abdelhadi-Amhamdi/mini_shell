/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:22 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/08 22:50:20 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void exec_cmd(t_tree *node, int p1, int p2, int std, int old)
{
	// pid_t pid;
	
	node->args = cmd_args_list_to_tabs(node);
	node->id = fork();
	if (!node->id)
	{
		dup2(p2, std);
		close(p2);
		if (old != -1)
			dup2(old, 1);
		close(p1);
		if (node->is_builtin)
		{
			exec_builtin(node, &app->env_list);
			exit (0);
		}
		else
			execve(node->args[0], node->args, NULL);
	}
	ft_free(node->args);
}

void run_pipe(t_tree *cmd, int *pipe, int in, int out, int side)
{
	int		std_file;
	int		used_end;
	int		unused_end;
	int		old;
	
	used_end = in;
	unused_end = pipe[1];
	std_file = STDIN_FILENO;
	old = out;
	if (side == 1)
	{
		used_end = out;
		unused_end = pipe[0];
		std_file = STDOUT_FILENO;
		old = -1;
	}
	if (cmd->type == PIPE)
		run_pipeline(cmd, in, used_end);
	else if (cmd->type == CMD)
		exec_cmd(cmd, unused_end, used_end, std_file, old);
	else
		executer(cmd, in, out);
}

int run_pipeline(t_tree *pipe_node, int in, int out)
{
	int fds[2];
	// int status;

	
	pipe(fds);
	run_pipe(pipe_node->left, fds, in, fds[1], 1);
	run_pipe(pipe_node->right, fds, fds[0], out, 2);
	close(fds[1]);
	close(fds[0]);
	if (out != 1)
		close(out);
	// wait(&status);
	// wait(&status);
	// set_exit_status(status);
	return (0);
}
