/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:49:28 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/24 11:07:56 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	destroy_ast_tree(t_tree *root)
{
	t_tree	*right;

	if (!root)
		return ;
	right = NULL;
	destroy_ast_tree(root->left);
	right = root->right;
	if (root->cmd_args)
		ft_free_lexer_list(&root->cmd_args);
	if (!root->is_op && root->path)
		free(root->path);
	if (root->type == HEREDOC_FILE)
		unlink(root->str);
	root->path = NULL;
	free(root->str);
	free(root);
	root = NULL;
	root = NULL;
	destroy_ast_tree(right);
}

void	destroy_pipes(t_pipes *list)
{
	t_pipes	*tmp;
	t_pipes	*next;

	tmp = list;
	while (tmp)
	{
		free(tmp->pipe);
		tmp->pipe = NULL;
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	destroy_main(t_main *main)
{
	if (main->ast)
		destroy_ast_tree(main->ast);
	main->ast = NULL;
	if (main->pipes)
		destroy_pipes(main->pipes);
	main->pipes = NULL;
}

void	_files(t_tree *root, int t)
{
	int	fd;

	if (!root)
		return ;
	fd = -1;
	_files(root->left, t);
	if ((root->type == RDIR || root->type == APND) && t == 1)
	{
		if (root->type == RDIR && root->str[0] == '>')
			fd = open(root->right->str, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (root->type == RDIR && root->str[0] == '<')
			fd = open(root->right->str, O_RDONLY, 0644);
		else if (root->type == APND)
			fd = open(root->right->str, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
		{
			printf("mini-sh: %s: No such file or directory\n", root->right->str);
			g_exit_status = 1;
		}
		root->right->id = fd;
	}
	if ((root->type == RDIR || root->type == APND) && t == 2)
		close(root->right->id);
	_files(root->right, t);
}

int	main(int ac, char **av, char **envp)
{
	char	*cmd;
	t_main	*main;

	main = init(envp, ac, av);
	if (!main)
		return (0);
	while (1)
	{
		cmd = readline("mini-sh1.0$ ");
		if (!cmd)
			break ;
		if (cmd[0])
		{
			main->ast = formater(cmd, main);
			if (main->ast)
			{
				executer(main->ast, main);
				destroy_main(main);
			}
			add_history(cmd);
		}
		free(cmd);
	}
	exit (g_exit_status);
}
