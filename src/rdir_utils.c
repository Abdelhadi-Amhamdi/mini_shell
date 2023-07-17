/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:24:24 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/17 14:27:13 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	exec__rdir_cmd(t_tree *cmd, t_pipe_data p_data, t_main *data)
{
	if (!cmd)
		return ;
	if (cmd->left && cmd->left->type == CMD)
		exec_pipe_cmd(cmd->left, p_data, data);
	else if (cmd->left && !cmd->left->is_op)
		exec_pipe_unk(cmd->left, p_data, data);
	else if (cmd->left && (cmd->left->type == RDIR \
	|| cmd->left->type == APND))
		exec_rdir_pipes(p_data, cmd->left, data);
}
