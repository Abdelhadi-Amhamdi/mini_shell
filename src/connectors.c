/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:04:02 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/18 15:02:16 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	wait_left(t_tree *root)
{
	int	status;

	if (!root)
		return ;
	wait_left(root->left);
	if (root->type == CMD && root->id > 0 && !root->is_builtin)
	{
		waitpid(root->id, &status, 0);
		root->id = DONT_WAITPID;
		exit_status = WEXITSTATUS(status);
	}
	wait_left(root->right);
}

void	run_connectors(t_tree *root, int in, int out, t_main *data)
{
	if (!ft_strncmp(root->str, "&&", ft_strlen(root->str)))
	{
		executer(root->left, in, out, data);
		wait_left(root->left);
		if (!exit_status)
			executer(root->right, in, out, data);
	}
	else
	{
		executer(root->left, in, out, data);
		wait_left(root->left);
		if (exit_status)
			executer(root->right, in, out, data);
	}
}
