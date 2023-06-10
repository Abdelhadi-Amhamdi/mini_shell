/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:29:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/10 14:39:05 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int run_cmd(t_tree *cmd, int in, int out)
{
	int status;

	status = 0;
	cmd->args = cmd_args_list_to_tabs(cmd);
	if (!cmd->args)
		return (perror(cmd->str), COMMAND_NOT_FOUND_EXIT_STATUS);
	if(cmd->is_builtin)
		return (exec_builtin(cmd, &app->env_list));
	cmd->id = fork();
	if (!cmd->id)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		execve(cmd->args[0], cmd->args, env_list_to_tabs(app->env_list));
	}
	ft_free(cmd->args);
	return (status);
}

int	exec_builtin(t_tree	*cmd, t_env	**env)
{
	if(!ft_strncmp(cmd->str, "cd", 2))
		return (ft_cd(*env,cmd));
	else if(!ft_strncmp(cmd->str, "env", 3))
		return (ft_env(*env));
	else if ( !ft_strncmp(cmd->str, "unset", 6))
		*env = ft_unset(cmd, *env);
	else if (!ft_strncmp(cmd->str, "export", 6))
		return (ft_export(cmd, env));
	else if (!ft_strncmp(cmd->str, "echo", 5))
		return (ft_echo(cmd));
	else if (!ft_strncmp(cmd->str, "pwd", 3))
		return (ft_pwd());
	else if (!ft_strncmp(cmd->str, "exit", 5))
		ft_exit();
	return (0);
}

int executer(t_tree *root, int in, int out)
{
	if (!root)
		return (app->status);
	if (root->type == CMD)
		app->status = run_cmd(root, in, out);
	else if (root->type == RDIR || root->type == APND)
		app->status = redirection_helper(root, in, out);
	else if (root->type == UNK || root->type == SPACE)
	{
		app->status = COMMAND_NOT_FOUND_EXIT_STATUS;
		perror(root->str);
	}
	else if (root->type == AND || root->type == OR)
		app->status = run_connectors(root, in, out);
	else if (root->type == PIPE)
		app->status = run_pipeline(root, out);
	return (app->status);
}