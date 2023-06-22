/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:29:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/22 18:46:07 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	close_all_pipes(t_main *data, int fd1, int fd2)
{
	t_pipes	*p_tmp;

	if (data->pipes)
	{
		p_tmp = data->pipes;
		while (p_tmp)
		{
			if (p_tmp->pipe[0] != fd1 && p_tmp->pipe[0] != fd2)
				close(p_tmp->pipe[0]);
			if (p_tmp->pipe[1] != fd1 && p_tmp->pipe[1] != fd2)
				close(p_tmp->pipe[1]);
			p_tmp = p_tmp->next;
		}
	}
}

void	run_cmd(t_tree *cmd, int in, int out, t_main *data)
{
	int	wait;

	wait = cmd->id;
	cmd->args = cmd_args_list_to_tabs(cmd, data);
	// int i= 0;
	// puts("========================================");
	// while(cmd->args[i])
	// {
	// 	printf(":%s: %p\n",cmd->args[i], cmd->args[i]);
	// 	i++;
	// }
	// puts("========================================");
	// return ;
	if (cmd->is_builtin)
	{
		g_exit_status = exec_builtin(cmd, &data->env, data, out);
		ft_free(cmd->args);
		return ;
	}
	cmd->id = fork();
	if (!cmd->id)
	{
		if (!ft_strncmp(cmd->str, "app", 3))
			signal(SIGINT, sig_int_handler);
		else
			signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(in, STDIN_FILENO);
		if (in)
			close (in);
		dup2(out, STDOUT_FILENO);
		if (out != 1)
			close(out);
		close_all_pipes(data, STDIN_FILENO, STDOUT_FILENO);
		if (execve(cmd->args[0], cmd->args, env_list_to_tabs(data->env)) == -1)
			exit (errno);
	}
	else
		g_exit_status = -1;
	ft_free(cmd->args);
	if (wait != DONT_WAITPID)
		wait_for_child(cmd);
}

int	exec_builtin(t_tree	*cmd, t_env	**env, t_main *data, int out)
{
	if (!ft_strncmp(cmd->str, "cd", 2))
		return (ft_cd(*env, cmd));
	else if (!ft_strncmp(cmd->str, "env", 3))
		return (ft_env(*env, out));
	else if (!ft_strncmp(cmd->str, "unset", 6))
		*env = ft_unset(cmd, *env);
	else if (!ft_strncmp(cmd->str, "export", 6))
		return (ft_export(cmd, env, out));
	else if (!ft_strncmp(cmd->str, "echo", 5))
		return (ft_echo(cmd, out));
	else if (!ft_strncmp(cmd->str, "pwd", 3))
		return (ft_pwd(*env, out));
	else if (!ft_strncmp(cmd->str, "exit", 5))
		ft_exit(cmd, data->ast);
	return (0);
}

void	exec_unknown(t_tree *cmd, int in, int out, t_main *data)
{
	expand_var_to_cmd(cmd, data);
	cmd->args = cmd_args_list_to_tabs(cmd, data);
	if (!cmd->args)
		return ;
	cmd->type = CMD;
	if (cmd->is_builtin)
	{
		g_exit_status = exec_builtin(cmd, &data->env, data, 1);
		return ;
	}
	cmd->id = fork();
	if (!cmd->id)
	{
		if (!ft_strncmp(cmd->str, "./app", 6))
			signal(SIGINT, sig_int_handler);
		else
			signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(in, STDIN_FILENO);
		if (in)
			close(in);
		dup2(out, STDOUT_FILENO);
		if (out > 1)
			close(out);
		if (execve(cmd->args[0], cmd->args, env_list_to_tabs(data->env)) == -1)
		{
			if (errno == ENOENT)
			{
				ft_putstr_fd("mini-sh: ", 2);
				ft_putstr_fd(cmd->str, 2);
				ft_putendl_fd(": command not found", 2);
			}
			exit (errno);
		}
	}
	else
	{
		if (!ft_strncmp(cmd->str, "./app", 6))
			g_exit_status = -1;
	}
	ft_free(cmd->args);
	cmd->args = NULL;
	if (out == 1)
		wait_for_child(cmd);
}

void	executer(t_tree *root, int in, int out, t_main *data)
{
	if (!root)
		return ;
	if (root->type == CMD)
		run_cmd(root, in, out, data);
	else if (root->type == RDIR || root->type == APND)
		redirection_helper(root, in, out, data);
	else if (root->type == AND || root->type == OR)
	{
		if (out != STDOUT_FILENO)
			out = STDOUT_FILENO;
		run_connectors(root, in, out, data);
	}
	else if (root->type == PIPE)
		run_pipeline(root, out, data);
	else if (root->type != HEREDOC_FILE)
		exec_unknown(root, in, out, data);
}
