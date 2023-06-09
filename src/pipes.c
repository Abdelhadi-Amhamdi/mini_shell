/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:22 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/09 15:15:00 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void exec_cmd(t_tree *node)
{
	if (node->is_builtin)
	{
		exec_builtin(node, &app->env_list);
		exit (0);
	}
	else
		execve(node->args[0], node->args, NULL);
}

void run_pipe(t_tree *cmd, int *pipe, int out, int side)
{
	int		std_file;
	int		used_end;
	int		unused_end;
	
	used_end = pipe[0];
	unused_end = pipe[1];
	std_file = STDIN_FILENO;
	if (side == 1)
	{
		used_end = pipe[1];
		unused_end = pipe[0];
		std_file = STDOUT_FILENO;
	}
	if (cmd->type == CMD)
	{
		cmd->args = cmd_args_list_to_tabs(cmd);
		cmd->id = fork();
		if (!cmd->id)
		{
			close(unused_end);
			dup2(used_end, std_file);
			close(used_end);
			dup2(out, STDOUT_FILENO);
			if (out != STDOUT_FILENO && out != -1)
				close(out);
			exec_cmd(cmd);	
		}
		ft_free(cmd->args);
	}
	else
		executer(cmd, STDIN_FILENO, used_end);
}

int run_pipeline(t_tree *pipe_node, int out)
{
	int fds[2];
	// int status;

	pipe(fds);
	run_pipe(pipe_node->left, fds, -1, 1);
	run_pipe(pipe_node->right, fds, out, 2);
	if (out != STDOUT_FILENO)
		close(out);
	close(fds[1]);
	close(fds[0]);
	// set_exit_status(status);
	return (0);
}
