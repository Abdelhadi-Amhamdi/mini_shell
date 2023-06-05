/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:22 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/05 14:15:48 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void exec_cmd(t_tree *node, int p1, int p2, int std, int old)
{
	pid_t pid;
	char **args;
	
	pid = fork();
	args = cmd_args_list_to_tabs(node);
	// if (node->is_builtin)
	// 	exec_builtin(node, NULL);
	if (!pid)
	{
		dup2(p2, std);
		close(p2);
		if (old != -1)
			dup2(old, 1);
		close(p1);
		execve(args[0], args, NULL);
	}
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
		executer(cmd, NULL);
}

int run_pipeline(t_tree *pipe_node, int in, int out)
{
	int fds[2];
	int status;

	pipe(fds);
	run_pipe(pipe_node->left, fds, in, fds[1], 1);
	run_pipe(pipe_node->right, fds, fds[0], out,  2);
	close(fds[1]);
	close(fds[0]);
	if (out != 1)
		close(out);
	wait(&status);
	wait(&status);
	return (status);
}

int run_cmd(t_tree *cmd, t_env **env)
{
	pid_t pid;
	int status;
	char **args;

	args = cmd_args_list_to_tabs(cmd);
	// if(cmd->is_builtin)
	// 	return (exec_builtin(cmd, env));
	pid = fork();
	if (!pid)
		execve(args[0], args, env_list_to_tabs(*env));
	waitpid(pid , &status, 0);
	return (status);
}

int run_rdir(t_tree *node)
{
	int file_fd;
	int flags;
	int status;

	flags = O_CREAT | O_RDWR | O_APPEND;
	status = 0;
	if (node->type == RDIR)
	{
		flags = O_CREAT | O_RDWR;
		unlink(node->right->str);
	}
	file_fd = open(node->right->str, flags, 0644);
	if (file_fd == -1)
		return (-1);
	if (node->left->type == PIPE)
		run_pipeline(node->left, 0, file_fd);
	else if (node->left->type == CMD)
	{
		exec_cmd(node->left, -1, file_fd, 1, -1);
		close(file_fd);
		wait(&status);
	}
	else
		status = executer(node->left, NULL);
	return (status);
}
