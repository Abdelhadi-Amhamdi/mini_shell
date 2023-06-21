/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:04:02 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/21 20:47:50 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	run_connectors(t_tree *root, int in, int out, t_main *data)
{
	if (!ft_strncmp(root->str, "&&", ft_strlen(root->str)))
	{
		executer(root->left, in, out, data);
		if (!g_exit_status)
			executer(root->right, in, out, data);
	}
	else
	{
		executer(root->left, in, out, data);
		if (g_exit_status)
			executer(root->right, in, out, data);
	}
}

void	wait_for_child(t_tree *cmd)
{
	int	status;
	int	signal_num;

	waitpid(cmd->id, &status, 0);
	if (WIFEXITED(status))
		perror_sstatus(status, cmd->str);
	else
	{
		signal_num = WTERMSIG(status);
		if (signal_num == SIGQUIT)
			printf("Quite\n");
		else if (signal_num == SIGINT)
			printf("\n");
		g_exit_status = 128 + signal_num;
	}
}
