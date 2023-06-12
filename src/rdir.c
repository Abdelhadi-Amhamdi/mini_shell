/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:22:47 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/12 20:24:46 by aamhamdi         ###   ########.fr       */
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

void run_redir_input(char *file_name, t_tree *cmd, int in, int out, t_tree *tree)
{
	int file_fd;
	
	file_fd = open(file_name, O_RDONLY, 0644);
	if (file_fd == -1)
	{
		printf("mini-sh: %s: No such file or directory\n", file_name);	
		return ;
	}
    if (in != 0)
        file_fd = in;
    executer(cmd, file_fd, out, tree);
}
void run_redir_output(char *file_name, t_tree *cmd, int in, int out, t_tree *tree)
{
	int file_fd;
	file_fd = open(file_name, O_CREAT| O_TRUNC | O_RDWR, 0644);\
	if (file_fd == -1)
		return ;
    if (out != 1)
        file_fd = out;
	executer(cmd, in, file_fd, tree);
}

void run_apand_function(char *file_name, t_tree *cmd, int in, int out, t_tree *tree)
{
	int file_fd;

	file_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (file_fd == -1)
		return ;
	if (out != 1)
		file_fd = out;
	executer(cmd, in, file_fd, tree);
}

void redirection_helper(t_tree *node, int in, int out, t_tree *tree)
{
	if (node->type == APND)
		run_apand_function(node->right->str, node->left, in, out, tree);
	else
	{
		if (node->str[0] == '<')
			run_redir_input(node->right->str, node->left, in, out, tree);
		else
			run_redir_output(node->right->str, node->left, in, out, tree);
	}
}
