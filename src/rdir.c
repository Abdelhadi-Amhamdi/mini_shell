/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:22:47 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/14 12:33:03 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

// void exec_redir_cmd(t_tree *cmd, int in, int out)
// {
// 	pid_t pid;

// 	cmd->args = cmd_args_list_to_tabs(cmd);
// 	pid = fork();
// 	if (!pid)
// 	{
// 		dup2(in, STDIN_FILENO);
// 		dup2(out, STDOUT_FILENO);
// 		if (cmd->is_builtin)
// 			exec_builtin(cmd, &app->env_list);
// 		else
// 			execve(cmd->args[0], cmd->args, env_list_to_tabs(app->env_list));
// 	}
// 	if (in != 0)
// 		close(in);
// 	if (out != 1)
// 		close(out);
// 	wait(NULL);
// }

t_lexer *creat_lexer_node(char *data)
{
	t_lexer *node;

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

void run_redir_input(t_tree *node, int in, int out, t_main *data)
{
	t_tree	*right;
	int fd;

	right = node->right;
	fd = open(right->str, O_RDONLY, 0644);
	if (fd == -1)
	{
		printf("mini-sh: %s: No such file or directory\n", right->str);
		exit_status = 1;
		return ;
	}
	if (in != 0)
		fd = out;
    executer(node->left, fd, out, data);
	close(fd);
}
void run_redir_output(char *file_name, t_tree *cmd, int in, int out, t_main *data)
{
	int file_fd;
	file_fd = open(file_name, O_CREAT| O_TRUNC | O_RDWR, 0644);
	if (file_fd == -1)
		return ;
    if (out != 1)
	{
		close(file_fd);
        file_fd = out;
	}
	executer(cmd, in, file_fd, data);
	close(file_fd);
}

void run_apand_function(char *file_name, t_tree *cmd, int in, int out, t_main *data)
{
	int file_fd;

	file_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (file_fd == -1)
		return ;
	if (out != 1)
		file_fd = out;
	executer(cmd, in, file_fd, data);
	close(file_fd);
}

void redirection_helper(t_tree *node, int in, int out, t_main *data)
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
