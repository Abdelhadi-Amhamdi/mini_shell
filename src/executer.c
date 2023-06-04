/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:29:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/04 15:22:13 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	exec_builtin(t_tree	*cmd, t_env	**env)
{
	if(!ft_strncmp(cmd->str, "cd", 2))
		ft_cd(*env,cmd);
	else if(!ft_strncmp(cmd->str, "env", 3))
		ft_env(*env);
	else if ( !ft_strncmp(cmd->str, "unset", 6))
		*env = ft_unset(cmd, *env);
	else if (!ft_strncmp(cmd->str, "export", 6))
		ft_export(cmd, env);
	else if (!ft_strncmp(cmd->str, "echo", 5))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd->str, "pwd", 3))
		ft_pwd();
	// else if (!ft_strncmp(cmd->str, "exit", 5))
	// 	ft_exit();
}

int executer(t_tree *root, t_app *app)
{
	if (root->type == CMD)
		return (run_cmd(root, &app->env_list));
	else if (root->type == PIPE)
		return (run_pipeline(root, 0, 1));
	else if (root->type == RDIR || root->type == APND)
		return (run_rdir(root));
	else if (root->type == HEREDOC)
		return (herdoc(root, app));
	else if (root->type == AND || root->type == OR)
		return (run_connectors(root, app));
	return (-1);
}