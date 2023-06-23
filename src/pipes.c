/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:22 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/23 22:03:35 by aamhamdi         ###   ########.fr       */
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

void	exec_rdir_pipes(t_pipe_data p_data, t_tree *cmd, t_main *data)
{
	int	fd;

	fd = _get_rdir_file_fd(cmd);
	if (p_data.side == LEFT_CHILD && cmd->str[0] == '<')
	{
		p_data.std_file = STDIN_FILENO;
		p_data.out = p_data.used_end;
		p_data.used_end = fd;
	}
	else if (p_data.side == RIGHT_CHILD && cmd->str[0] == '>')
		p_data.out = fd;
	else
		p_data.used_end = fd;
	if (fd == -1)
		return ;
	if (cmd->left)
		exec_pipe_cmd(cmd->left, p_data, data);
	close(fd);
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
	else
	{
		executer_helper(cmd, STDIN_FILENO, p_data.used_end, data);
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
