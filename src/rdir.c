/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:22:47 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/22 10:09:19 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_lexer	*creat_lexer_node(char *data)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->id = 0;
	node->is_builtin = 0;
	node->is_oper = 0;
	node->next = NULL;
	node->path = NULL;
	node->str = ft_strdup(data);
	node->type = FL;
	return (node);
}

int	_get_rdir_file_fd(t_tree *node, int open)
{
	t_tree	*right;

	if (node && node->right)
	{
		right = node->right;
		if (right->id == -1 && open == 1)
			ft_p_error(NFD, right, 1);
		return (right->id);
	}
	return (-1);
}

void	rdir_helper(t_tree *root, int in, int out, t_main *data)
{
	int	fd;

	fd = _get_rdir_file_fd(root, data->open);
	if (fd == -1)
		return ;
	if (root->str[0] == '>')
	{
		if (out != 1)
			fd = out;
		executer_helper(root->left, in, fd, data);
	}
	else
	{
		if (in != 0)
			fd = in;
		executer_helper(root->left, fd, out, data);
	}
}

void	close_all_pipes(t_main *data, int fd1, int fd2)
{
	t_pipes	*p_tmp;

	if (data->pipes)
	{
		p_tmp = data->pipes;
		while (p_tmp)
		{
			if (p_tmp->pipe[0] != fd1 && p_tmp->pipe[0] != fd2)
				close(p_tmp->pipe[0]);
			if (p_tmp->pipe[1] != fd1 && p_tmp->pipe[1] != fd2)
				close(p_tmp->pipe[1]);
			p_tmp = p_tmp->next;
		}
	}
}

int	exec_rdir_pipes(t_pipe_data p_data, t_tree *cmd, t_main *data)
{
	int	fd;

	fd = _get_rdir_file_fd(cmd, data->open);
	if (fd == -1)
		return (0);
	if (!p_data.is_rdir && cmd->str[0] == '>')
	{
		p_data.out = 1;
		p_data.is_rdir = true;
	}
	if (cmd->str[0] == '<' && p_data.side == LEFT_CHILD && p_data.out == -1)
	{
		p_data.std_file = STDIN_FILENO;
		p_data.out = p_data.used_end;
		p_data.used_end = fd;
	}
	else if (cmd->str[0] == '<' && p_data.out == 1 && !p_data.is_rdir)
	{
		p_data.used_end = fd;
		p_data.is_rdir = true;
	}
	else if (cmd->str[0] == '>' && p_data.out == 1)
		p_data.out = fd;
	exec__rdir_cmd(cmd, p_data, data);
	return (close(fd));
}
