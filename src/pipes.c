/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:22 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/25 22:21:36 by aamhamdi         ###   ########.fr       */
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
		env = env_tabs(data->env);
		if (execve(node->args[0], node->args, env) == -1)
		{
			if (errno == ENOENT)
			{
				ft_putstr_fd("mini-sh: ", 2);
				ft_putstr_fd(node->str, 2);
				ft_putendl_fd(": command not found", 2);
			}
			exit (errno);
		}
	}
}

void	exec_pipe_cmd(t_tree *cmd, t_pipe_data p_data, t_main *data)
{
	cmd->args = _args_tabs(cmd, data);
	cmd->type = CMD;
	cmd->id = _ft_fork();
	if (cmd->id == -1)
		return ;
	if (!cmd->id)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(p_data.unused_end);
		if (_ft_dup2(p_data.used_end, p_data.std_file))
			return ;
		if (_ft_dup2(p_data.out, STDOUT_FILENO))
			return ;
		close_all_pipes(data, p_data.used_end, p_data.unused_end);
		exec_cmd(cmd, data);
	}
}

void	exec_pipe_unk(t_tree *cmd, t_pipe_data p_data, t_main *data)
{
	expand_var_to_cmd(cmd, data);
	cmd->args = _args_tabs(cmd, data);
	if (!cmd->args || !cmd->str)
		return ;
	cmd->type = CMD;
	cmd->id = _ft_fork();
	if (cmd->id == -1)
		return ;
	if (!cmd->id)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(p_data.unused_end);
		if (_ft_dup2(p_data.used_end, p_data.std_file))
			return ;
		if (_ft_dup2(p_data.out, STDOUT_FILENO))
			return ;
		close_all_pipes(data, p_data.used_end, p_data.unused_end);
		exec_cmd(cmd, data);
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
		exec_rdir_pipes(p_data, cmd, data);
	else if (cmd->type == UNK || cmd->type == VAR)
		exec_pipe_unk(cmd, p_data, data);
	else
	{
		if (p_data.side == LEFT_CHILD)
			executer_helper(cmd, STDIN_FILENO, p_data.used_end, data);
		else
			executer_helper(cmd, p_data.used_end, STDOUT_FILENO, data);
		close(p_data.used_end);
		if (p_data.out != 1)
			close(p_data.out);
	}
}

void	run_pipeline(t_tree *pipe_node, int out, t_main *data)
{
	int			*fds;
	t_pipe_data	p_data;

	fds = _ft_pipe(data);
	if (!fds)
		return ;
	p_data.out = -1;
	p_data.side = LEFT_CHILD;
	run_pipe(pipe_node->left, fds, p_data, data);
	p_data.side = RIGHT_CHILD;
	p_data.out = out;
	run_pipe(pipe_node->right, fds, p_data, data);
	if (out != STDOUT_FILENO)
		close(out);
	close(fds[PIPE_WRITE_END]);
	close(fds[PIPE_READ_END]);
	if (out == 1)
	{
		wait_for_last(pipe_node->right);
		if (g_exit_status == -1)
			g_exit_status = 0;
	}
}
