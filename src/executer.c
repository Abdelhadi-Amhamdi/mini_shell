/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:29:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/19 15:49:36 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	run_cmd(t_tree *cmd, int in, int out, t_main *data)
{
	cmd->args = _args_tabs(cmd, data);
	if (cmd->is_builtin)
		g_exit_status = exec_builtin(cmd, &data->env, data, out);
	else
	{
		cmd->id = _ft_fork();
		if (cmd->id == -1)
			return ;
		if (!cmd->id)
			_exec(cmd, in, out, data);
		else
			g_exit_status = -1;
		wait_for_child(cmd);
	}
}

int	exec_builtin(t_tree	*cmd, t_env	**env, t_main *data, int out)
{
	if (!ft_strncmp(cmd->str, "cd", 2))
		return (ft_cd(*env, cmd, data));
	else if (!ft_strncmp(cmd->str, "env", 3))
		return (ft_env(*env, out));
	else if (!ft_strncmp(cmd->str, "unset", 6))
		*env = ft_unset(cmd, *env);
	else if (!ft_strncmp(cmd->str, "export", 6))
		return (ft_export(cmd, env, out));
	else if (!ft_strncmp(cmd->str, "echo", 5))
		return (ft_echo(cmd, out));
	else if (!ft_strncmp(cmd->str, "pwd", 3))
		return (ft_pwd(*env, out, data));
	else if (!ft_strncmp(cmd->str, "exit", 5))
		return (ft_exit(cmd, data));
	return (0);
}

void	exec_unknown(t_tree *cmd, int in, int out, t_main *data)
{
	expand_var_to_cmd(cmd, data);
	cmd->args = _args_tabs(cmd, data);
	if (!cmd->args || !cmd->str)
		return ;
	cmd->type = CMD;
	if (cmd->is_builtin)
		g_exit_status = exec_builtin(cmd, &data->env, data, 1);
	else
	{
		cmd->id = _ft_fork();
		if (cmd->id == -1)
			return ;
		if (!cmd->id)
			_exec_unk(cmd, in, out, data);
		else
		{
			if (!ft_strncmp(cmd->str, "./minishell", 12))
				g_exit_status = -1;
		}
		if (out == 1)
			wait_for_child(cmd);
	}
}

void	executer_helper(t_tree *root, int in, int out, t_main *data)
{
	if (!root)
		return ;
	if (root->type == CMD)
		run_cmd(root, in, out, data);
	else if (root->type == RDIR || root->type == APND)
		rdir_helper(root, in, out, data);
	else if (root->type == AND || root->type == OR)
		run_connectors(root, STDIN_FILENO, STDOUT_FILENO, data);
	else if (root->type == PIPE)
		run_pipeline(root, out, data);
	else if (root->type != HEREDOC_FILE)
		exec_unknown(root, in, out, data);
}

void	executer(t_tree *root, t_main *data)
{
	pid_t	pid;

	_files(root, 1, data);
	executer_helper(root, STDIN_FILENO, STDOUT_FILENO, data);
	pid = waitpid(-1, NULL, 0);
	while (pid > 0)
		pid = waitpid(-1, NULL, 0);
	_files(root, 2, data);
}
