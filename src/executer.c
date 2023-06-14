/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:29:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/14 08:41:23 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void run_cmd(t_tree *cmd, int in, int out, t_main *data)
{
	cmd->args = cmd_args_list_to_tabs(cmd, data);
	if (!cmd->args && !cmd->is_builtin)
	{
		exit_status = COMMAND_NOT_FOUND_EXIT_STATUS;
		printf("mini-sh: %s: command not found!\n", cmd->str);
		return ;
	}
	if(cmd->is_builtin)
	{
		exit_status = exec_builtin(cmd, &data->env, data, out);
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
		execve(cmd->args[0], cmd->args, env_list_to_tabs(data->env));
	}
	else
		exit_status = -1;
	ft_free(cmd->args);
}

int	exec_builtin(t_tree	*cmd, t_env	**env, t_main *data, int out)
{
	if(!ft_strncmp(cmd->str, "cd", 2))
		return (ft_cd(*env,cmd));
	else if(!ft_strncmp(cmd->str, "env", 3))
		return (ft_env(*env, out));
	else if ( !ft_strncmp(cmd->str, "unset", 6))
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

void executer(t_tree *root, int in, int out, t_main *data)
{
	if (!root)
		return ;
	if (root->type == CMD || root->type == FL)
		run_cmd(root, in, out, data);
	else if (root->type == RDIR || root->type == APND)
		redirection_helper(root, in, out, data);
	else if (root->type == UNK || root->type == W_SPACE)
	{
		exit_status = COMMAND_NOT_FOUND_EXIT_STATUS;
		printf("mini-sh: %s: command not found!\n", root->str);
	}
	else if (root->type == AND || root->type == OR)
	{
		if (out != STDOUT_FILENO)
			out  = STDOUT_FILENO;
		run_connectors(root, in, out, data);
	}
	else if (root->type == PIPE)
		run_pipeline(root, out, data);
}