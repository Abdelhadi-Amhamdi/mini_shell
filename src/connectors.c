/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:04:02 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/17 15:27:58 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	run_connectors(t_tree *root, int in, int out, t_main *data)
{
	if (!ft_strncmp(root->str, "&&", ft_strlen(root->str)))
	{
		executer_helper(root->left, in, out, data);
		if (!g_exit_status)
			executer_helper(root->right, in, out, data);
	}
	else
	{
		executer_helper(root->left, in, out, data);
		if (g_exit_status)
			executer_helper(root->right, in, out, data);
	}
}

void	wait_for_child(t_tree *cmd)
{
	int	status;
	int	signal_num;

	waitpid(cmd->id, &status, 0);
	if (WIFEXITED(status))
		perror_sstatus(status, cmd->is_builtin);
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

int	*_ft_pipe(t_main *data)
{
	t_pipes	*p;
	int		*fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		return (ft_putendl_fd("MALLOC FAILED!", 2), NULL);
	if (pipe(fds) == -1)
		return (ft_putendl_fd("PIPE FAILED!", 2), free (fds), NULL);
	p = pipe_node_create(&fds);
	if (!p)
		return (ft_putendl_fd("MALLOC FAILED!", 2), free (fds), NULL);
	add_to_end(&data->pipes, p);
	return (fds);
}

int	_ft_dup2(int new, int old)
{
	if (new < 0 || old < 0)
		return (0);
	if (dup2(new, old) == -1)
		return (ft_putendl_fd("DUP2 FAILED!", 2), 1);
	if (new > 1)
		close (new);
	return (0);
}

int	_ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("FORK FAILED", 2);
		return (-1);
	}
	return (pid);
}
