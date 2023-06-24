/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:21:48 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/24 11:05:13 by aagouzou         ###   ########.fr       */
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

void	expand_var_to_cmd(t_tree *cmd, t_main *data)
{
	char	*tmp;

	if (cmd->type == VAR || ((cmd->type == UNK || cmd->type == SQ \
	|| cmd->type == DQ) && strchr(cmd->str, '$')))
	{
		tmp = cmd->str;
		cmd->str = expand(cmd->str, data->env);
		free(tmp);
		if (!cmd->str)
			return ;
		cmd->is_builtin = is_builtin(cmd->str);
	}
}
