/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:22 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/22 22:04:03 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	exec_cmd(t_tree *node, t_main *data)
{
	int		status ;
	char	**env;

	if (node->is_builtin)
	{
		status = exec_builtin(node, &data->env, data, 1);
		exit (status);
	}
	else
	{
		env = env_list_to_tabs(data->env);
		if (execve(node->args[0], node->args, env) == -1)
			exit (errno);
	}
}

void	exec_pipe_cmd(t_tree *cmd, t_pipe_data p_data, t_main *data)
{
	cmd->args = cmd_args_list_to_tabs(cmd, data);
	cmd->type = CMD;
	cmd->id = fork();
	if (!cmd->id)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(p_data.unused_end);
		dup2(p_data.used_end, p_data.std_file);
		close(p_data.used_end);
		dup2(p_data.out, STDOUT_FILENO);
		if (p_data.out > 1)
			close(p_data.out);
		close_all_pipes(data, p_data.used_end, p_data.unused_end);
		exec_cmd(cmd, data);
	}
	ft_free(cmd->args);
}

void	exec_rdir_pipes(t_tree *cmd, int used_end, int side, t_main *data)
{
	cmd->id = DONT_WAITPID;
	if (((cmd->type == RDIR && cmd->str[0] == '>') || cmd->type == APND))
	{
		if (side == LEFT_CHILD)
		{
			close(used_end);
			redirection_helper(cmd, STDIN_FILENO, STDOUT_FILENO, data);
		}
		else
			redirection_helper(cmd, used_end, STDOUT_FILENO, data);
	}
	else if (cmd->type == RDIR && cmd->str[0] == '<')
	{
		if (side == RIGHT_CHILD)
		{
			close(used_end);
			redirection_helper(cmd, STDIN_FILENO, STDOUT_FILENO, data);
		}
		else
			redirection_helper(cmd, STDIN_FILENO, used_end, data);
	}
}

void	run_pipe(t_tree *cmd, int *pipe, t_pipe_data p_data, t_main *data)
{
	p_data.unused_end = pipe[PIPE_WRITE_END];
	p_data.used_end = pipe[PIPE_READ_END];
	p_data.std_file = STDIN_FILENO;
	if (p_data.side == LEFT_CHILD)
	{
		p_data.used_end = pipe[PIPE_WRITE_END];
		p_data.unused_end = pipe[PIPE_READ_END];
		p_data.std_file = STDOUT_FILENO;
	}
	if (cmd->type == CMD)
		exec_pipe_cmd(cmd, p_data, data);
	else if (cmd->type == RDIR || cmd->type == APND)
		exec_rdir_pipes(cmd, p_data.used_end, p_data.side, data);
	else
	{
		executer(cmd, STDIN_FILENO, p_data.used_end, data);
		close(p_data.used_end);
		if (p_data.out != 1)
			close(p_data.out);
	}
}

void	run_pipeline(t_tree *pipe_node, int out, t_main *data)
{
	int			*fds;
	t_pipe_data	p_data;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		return ;
	pipe(fds);
	p_data.out = -1;
	p_data.side = LEFT_CHILD;
	add_to_end(&data->pipes, pipe_node_create(&fds));
	if (pipe_node->left)
		run_pipe(pipe_node->left, fds, p_data, data);
	p_data.side = RIGHT_CHILD;
	p_data.out = out;
	if (pipe_node->right)
		run_pipe(pipe_node->right, fds, p_data, data);
	if (out != STDOUT_FILENO)
		close(out);
	close(fds[PIPE_WRITE_END]);
	close(fds[PIPE_READ_END]);
	if (out == 1)
		wait_for_last(pipe_node->right);
}
