/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:22:47 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/16 11:04:16 by aamhamdi         ###   ########.fr       */
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

void	run_redir_input(t_tree *node, int in, int out, t_main *data)
{
	t_tree	*right;
	int		fd;

	right = node->right;
	fd = open(right->str, O_RDONLY, 0644);
	if (fd == -1)
	{
		printf("mini-sh: %s: No such file or directory\n", right->str);
		exit_status = 1;
		return ;
	}
	if (in != 0)
		fd = in;
	executer(node->left, fd, out, data);
	close(fd);
}

void	run_redir_output(t_tree *node, int in, int out, t_main *data)
{
	int		file_fd;
	char	*file_name;

	file_name = node->right->str;
	file_fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (file_fd == -1)
		return ;
	if (out != 1)
	{
		close(file_fd);
		file_fd = out;
	}
	executer(node->left, in, file_fd, data);
	close(file_fd);
}

void	run_apand_function(t_tree *node, int in, int out, t_main *data)
{
	int		file_fd;
	char	*file_name;

	file_name = node->right->str;
	file_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (file_fd == -1)
		return ;
	if (out != 1)
		file_fd = out;
	executer(node->left, in, file_fd, data);
	close(file_fd);
}

void	redirection_helper(t_tree *node, int in, int out, t_main *data)
{
	if (node->type == APND)
		run_apand_function(node->right->str, node->left, in, out, data);
	else
	{
		if (node->str[0] == '<')
			run_redir_input(node, in, out, data);
		else
			run_redir_output(node->right->str, node->left, in, out, data);
	}
}
