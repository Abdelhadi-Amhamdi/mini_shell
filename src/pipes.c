/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:22 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/24 13:18:16 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void exec_cmd(t_tree *node, int p1, int p2, int std, int old)
{
	pid_t pid;
	pid = fork();
	if (!pid)
	{
		dup2(p2, std);
		close(p2);
		if (old != -1)
			dup2(old, 1);
		close(p1);
		execve(node->cmd_args[0], node->cmd_args, NULL);
	}
}

void run_pipe(t_tree *cmd, int *pipe,int in, int out, int side)
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
	else
		exec_cmd(cmd, unused_end, used_end, std_file, old);
}

void run_pipeline(t_tree *pipe_node, int in, int out)
{
	int fds[2];

	pipe(fds);
	run_pipe(pipe_node->left, fds, in, fds[1], 1);
	run_pipe(pipe_node->right, fds, fds[0], out,  2);
	close(fds[1]);
	close(fds[0]);
	wait(NULL);
	wait(NULL);
}

void run_cmd(t_tree *cmd)
{
	pid_t pid;

	pid = fork();
	if (!pid)
		execve(cmd->cmd_args[0], cmd->cmd_args, NULL);
	wait(NULL);
}

void run_rdir(t_tree *node)
{
	int file_fd;

	unlink(node->right->str);
	file_fd = open(node->right->str, O_CREAT | O_RDWR, 0644);
	if (file_fd == -1)
	{
		printf("error in open\n");
		return ;
	}
	if (node->left->type == PIPE)
		run_pipeline(node->left, 0, file_fd);
	else
	{
		exec_cmd(node->left, -1, file_fd, 1, -1);
		wait(NULL);
	}
	close(file_fd);
}
