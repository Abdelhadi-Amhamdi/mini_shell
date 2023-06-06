/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:29:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/06 16:11:18 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

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

int executer(t_tree *root)
{
	if (root->type == CMD)
		return (run_cmd(root, &app->env_list));
	else if (root->type == PIPE)
		return (run_pipeline(root, 0, 1));
	else if (root->type == RDIR || root->type == APND)
		return (run_rdir(root, 1));
	else if (root->type == HEREDOC)
		return (herdoc(root));
	else if (root->type == AND || root->type == OR)
		return (run_connectors(root));
	else if (root->type == UNK)
		return (set_exit_status(127), printf("mini-sh: %s: command not found\n", root->str), -1);
	return (-1);
}