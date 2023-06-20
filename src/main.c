/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:49:28 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/20 16:22:24 by aagouzou         ###   ########.fr       */
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

void	wait_pids(t_tree *root)
{
	int	status;
	int	signal_num;

	if (!root)
		return ;
	wait_pids(root->left);
	if (root->type == CMD && root->id != DONT_WAITPID)
	{
		waitpid(root->id, &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else
		{
			signal_num = WTERMSIG(status);
			if (signal_num == SIGQUIT)
				printf("Quite\n");
			else if (signal_num == SIGINT)
				printf("\n");
			exit_status = 128 + signal_num;
		}
	}
	wait_pids(root->right);
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
		cmd = readline("\033[1;33mmini_sh-1.0$ \033[0m");
		if (!cmd)
			break ;
		if (cmd[0])
		{
			main->ast = formater(cmd, main);
			if (main->ast)
			{
				printTree(main->ast);
				executer(main->ast, STDIN_FILENO, STDOUT_FILENO, main);
				wait_pids(main->ast);
				destroy_main(main);
			}
			add_history(cmd);
			free(cmd);
		}
	}
	exit (exit_status);
}
