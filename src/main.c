/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:49:28 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/21 20:24:26 by aagouzou         ###   ########.fr       */
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
	if (!root->is_op && root->cmd_args)
		ft_free_lexer_list(&root->cmd_args);
	if (root->type == CMD && root->path)
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
				// printTree(main->ast);
				executer(main->ast, STDIN_FILENO, STDOUT_FILENO, main);
				while (wait(0) != -1);
				destroy_main(main);
			}
			add_history(cmd);
			free(cmd);
		}
	}
	exit (g_exit_status);
}
