/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:29:12 by aamhamdi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/16 12:55:45 by aagouzou         ###   ########.fr       */
=======
/*   Updated: 2023/06/16 23:35:44 by aamhamdi         ###   ########.fr       */
>>>>>>> b9747e2e754291f864e5fabd9d306cc7b2736886
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
	cmd->is_builtin = is_builtin(cmd->str);
	cmd->args = cmd_args_list_to_tabs(cmd, data);
	if (cmd->is_builtin)
	{
		exit_status = exec_builtin(cmd, &data->env, data, out);
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
		dup2(out, STDOUT_FILENO);
		close_all_pipes(data, STDIN_FILENO, STDOUT_FILENO);
		if (execve(cmd->args[0], cmd->args, env_list_to_tabs(data->env)) == -1)
			ft_putendl_fd("Error", 2);
	}
	else
		exit_status = -1;
	ft_free(cmd->args);
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
	int	status;

	cmd->args = cmd_args_list_to_tabs(cmd, data);
	if (!(*cmd->args))
		return ;
	cmd->id = fork();
	if (!cmd->id)
	{
		if (!ft_strncmp(cmd->str, "app", 3))
			signal(SIGINT, sig_int_handler);
		else
			signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		if (execve(cmd->args[0], cmd->args, env_list_to_tabs(data->env)) == -1)
			exit (errno);
	}
	else
		exit_status = -1;
	waitpid(cmd->id, &status, 0);
	perror_sstatus(status, cmd->args[0]);
}

void	executer(t_tree *root, int in, int out, t_main *data)
{
	if (!root)
		return ;
	if (root->type == CMD || root->type == FL)
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
	else
		exec_unknown(root, in, out, data);
}
