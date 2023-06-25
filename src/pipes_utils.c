/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 23:32:37 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/25 10:28:01 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_pipes	*pipe_node_create(int **pipe)
{
	t_pipes	*p;

	p = malloc(sizeof(t_pipes));
	if (!p)
		return (NULL);
	p->pipe = *pipe;
	p->next = NULL;
	return (p);
}

void	add_to_end(t_pipes **list, t_pipes *item)
{
	t_pipes	*tmp;

	if (!(*list))
		*list = item;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = item;
	}
}

int	_args_size(t_lexer *list)
{
	int		size;

	size = 0;
	while (list)
	{
		if (list && (list->type != W_SPACE || list->id == PREINTABLE_SPACE))
			size++;
		list = list->next;
	}
	return (size);
}

int	path_exist(char *path, char **paths)
{
	int	index;

	index = 0;
	while (paths[index])
	{
		if (!ft_strncmp(path, paths[index], ft_strlen(paths[index])))
			return (1);
		index++;
	}
	return (0);
}

void	wait_for_last(t_tree *cmd_right)
{
	t_tree	*cmd;
	int		status;
	int		signal_num;

	cmd = cmd_right;
	if (cmd_right->type == RDIR || cmd_right->type == APND)
		cmd = cmd_right->left;
	if (!cmd)
		g_exit_status = -1;
	else if (cmd->type == CMD && cmd->id != DONT_WAITPID)
	{
		waitpid(cmd->id, &status, 0);
		if (WIFEXITED(status))
			perror_sstatus(status, cmd->str);
		else if (WIFSIGNALED (status))
		{
			signal_num = WTERMSIG(status);
			if (signal_num == SIGQUIT)
				printf("Quite\n");
			else if (signal_num == SIGINT)
				printf("\n");
			g_exit_status = 128 + signal_num;
		}
	}
}
