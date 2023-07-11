/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:36:58 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/26 08:35:41 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*get_var_from_args(t_lexer *tmp, \
t_tree *node, char **paths, t_main *data)
{
	t_lexer	*tmp_list;

	node->str = expand(tmp->str, data->env);
	if (node->str)
	{
		if (tmp->path)
			node->path = ft_strdup(tmp->path);
		else
			node->path = get_path(node->str, paths);
		tmp_list = tmp->next;
		del_node(tmp);
		node->cmd_args = tmp_list;
		return (ft_free(paths), ft_strdup(node->str));
	}
	return (ft_free(paths), NULL);
}

char	*get_cmd_from_args(t_lexer *tmp, \
t_tree *node, char **paths)
{
	t_lexer	*tmp_list;

	node->str = ft_strdup(tmp->str);
	if (tmp->path)
		node->path = ft_strdup(tmp->path);
	else
		node->path = get_path(node->str, paths);
	tmp_list = tmp->next;
	if (!node->path)
		node->path = ft_strdup(tmp->str);
	del_node(tmp);
	node->cmd_args = tmp_list;
	return (ft_free(paths), ft_strdup(node->path));
}

char	*none_str(t_tree *node, t_main *data, char **paths)
{
	t_lexer	*tmp;
	t_lexer	*tmp_list;

	if (node->cmd_args)
	{
		tmp = node->cmd_args;
		while (tmp)
		{
			if (tmp->str && tmp->type != W_SPACE && strchr(tmp->str, '$'))
				return (get_var_from_args(tmp, node, paths, data));
			else if (tmp->str && tmp->type != W_SPACE)
				return (get_cmd_from_args(tmp, node, paths));
			tmp_list = tmp;
			tmp = tmp->next;
			del_node(tmp_list);
		}
	}
	node->cmd_args = NULL;
	return (ft_free(paths), NULL);
}

void	_exec_unk(t_tree *cmd, int in, int out, t_main *data)
{
	if (!ft_strncmp(cmd->str, "./minishell", 12))
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
		destroy_main(data, 1);  //bus error on this line of code
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
