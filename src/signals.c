/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:21:48 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/25 16:20:37 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	sig_int_handler(int type)
{
	if (type == SIGINT && (g_exit_status != -1))
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = EXIT_FAILURE;
	}
}

void	sigint_heredoc_handler(int type)
{
	if (type == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		exit (1);
	}
}

void	re_tokenize(t_tree *cmd, t_main *data)
{
	t_lexer	*new_list;
	t_lexer	*args_tmp;

	new_list = NULL;
	new_list = lexer(cmd->str, data->env);
	ft_expander(new_list, data->env);
	free(cmd->str);
	cmd->str = ft_strdup(new_list->str);
	if (!cmd->cmd_args)
		cmd->cmd_args = new_list->next;
	else
	{
		args_tmp = cmd->cmd_args;
		while (args_tmp->next)
			args_tmp = args_tmp->next;
		args_tmp->next = new_list->next;
	}
	del_node(new_list);
}

void	expand_var_to_cmd(t_tree *cmd, t_main *data)
{
	char	*tmp;
	char	**paths;

	if (cmd->type == VAR || ((cmd->type == UNK || cmd->type == SQ \
	|| cmd->type == DQ) && strchr(cmd->str, '$')))
	{
		tmp = cmd->str;
		cmd->str = expand(cmd->str, data->env);
		if (cmd->str && contain_spaces(cmd->str) && \
		(!is_match(cmd->str, "* ") || !is_match(cmd->str, " *")))
			re_tokenize(cmd, data);
		cmd->path = NULL;
		free(tmp);
		if (!cmd->str)
			return ;
		paths = all_paths(data->env);
		cmd->path = get_path(cmd->str, paths);
		ft_free (paths);
		cmd->is_builtin = is_builtin(cmd->str);
	}
}

void	destroy_pipes(t_pipes *list)
{
	t_pipes	*tmp;
	t_pipes	*next;

	tmp = list;
	while (tmp)
	{
		free(tmp->pipe);
		tmp->pipe = NULL;
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}
