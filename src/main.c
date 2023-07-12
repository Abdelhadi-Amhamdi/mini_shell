/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:49:28 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/12 09:08:25 by aamhamdi         ###   ########.fr       */
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
		_free_lexer(&root->cmd_args);
	if (!root->is_op && root->path)
		free(root->path);
	root->path = NULL;
	if (root->type == HEREDOC_FILE)
		unlink(root->str);
	if (!root->is_op && root->args)
		ft_free(root->args);
	root->args = NULL;
	free(root->str);
	free(root);
	root = NULL;
	root = NULL;
	destroy_ast_tree(right);
}

void	destroy_env(t_env *env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = env;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key)
			free(tmp->key);
		tmp->key = NULL;
		if (tmp->value)
			free(tmp->value);
		tmp->value = NULL;
		free (tmp);
		tmp = next;
	}
}

t_main	*destroy_main(t_main *main, int t)
{
	if (main->ast)
		destroy_ast_tree(main->ast);
	main->ast = NULL;
	if (main->pipes)
		destroy_pipes(main->pipes);
	main->pipes = NULL;
	if (t == 1)
	{
		destroy_env(main->env);
		main->env = NULL;
		free(main);
		main = NULL;
	}
	return (NULL);
}

void	_files(t_tree *root, int t, t_main *data)
{
	int	fd;

	if (!root)
		return ;
	fd = -1;
	_files(root->left, t, data);
	if ((root->type == RDIR || root->type == APND) && t == 1)
	{	
		if (expand_vars(root->right, data))
			return ;
		if (root->type == RDIR && root->str[0] == '>')
			fd = open(root->right->str, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (root->type == RDIR && root->str[0] == '<')
			fd = open(root->right->str, O_RDONLY, 0644);
		else if (root->type == APND)
			fd = open(root->right->str, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			ft_p_error(NFD, root->right, 1);
		root->right->id = fd;
	}
	if ((root->type == RDIR || root->type == APND) && t == 2)
		close(root->right->id);
	_files(root->right, t, data);
}

void test()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **envp)
{
	char	*cmd;
	t_main	*main;
	// atexit(test);
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
				executer(main->ast, main);
				destroy_main(main, 0);
			}
			add_history(cmd);
		}
		free(cmd);
	}
	main = destroy_main(main, 1);
	exit (g_exit_status);
}
