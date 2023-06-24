/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:36:58 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/24 11:07:39 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	check_path_exist(char *path, char **paths)
{
	if (!paths)
		return (1);
	if (path_exist(path, paths))
		return (0);
	return (1);
}

char	*none_str(t_tree *node)
{
	if (node->cmd_args)
	{
		node->str = ft_strdup(node->cmd_args->str);
		return (node->str);
	}
	return (NULL);
}

void	_exec_unk(t_tree *cmd, int in, int out, t_main *data)
{
	if (!ft_strncmp(cmd->str, "./app", 6))
		signal(SIGINT, sig_int_handler);
	else
		signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (_ft_dup2(in, STDIN_FILENO))
		return ;
	if (_ft_dup2(out, STDOUT_FILENO))
		return ;
	if (execve(cmd->args[0], cmd->args, env_tabs(data->env)) == -1)
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

void	_exec(t_tree *cmd, int in, int out, t_main *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (_ft_dup2(in, STDIN_FILENO))
		return ;
	if (_ft_dup2(out, STDOUT_FILENO))
		return ;
	if (execve(cmd->args[0], cmd->args, env_tabs(data->env)) == -1)
		exit (errno);
}
