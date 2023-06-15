/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:49:28 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/15 20:24:35 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void print_banner()
{
	puts("");
	puts("");
	printf("::::    ::::  ::::::::::: ::::    ::: :::::::::::               ::::::::  :::    ::: \n");
	printf("+:+:+: :+:+:+     :+:     :+:+:   :+:     :+:                  :+:    :+: :+:    :+: \n");
	printf("+:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+                  +:+        +:+    +:+ \n");
	printf("+#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+    +#++:++#++:++ +#++:++#++ +#++:++#++ \n");
	printf("+#+       +#+     +#+     +#+  +#+#+#     +#+                         +#+ +#+    +#+ \n");
	printf("#+#       #+#     #+#     #+#   #+#+#     #+#                  #+#    #+# #+#    #+# \n");
	printf("###       ### ########### ###    #### ###########               ########  ###    ### \n");
	puts("");
	puts("");
}

t_main *init(char **env)
{
	t_main *data;

	data = malloc(sizeof(t_main));
	if (!data)
		return (NULL);
	data->env = get_env_vars(env);
	data->ast = NULL;
	data->old_fds = NULL;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	return (data);
}

void destroy_ast_tree(t_tree *root)
{
	t_tree *right;

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

void wait_pids(t_tree *root)
{
	int status;
	if (!root)
		return ;
	wait_pids(root->left);
	if (root->type == CMD)
	{
		waitpid(root->id, &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else
		{
			int s = WTERMSIG(status);
			if (s  == SIGQUIT)
				printf("Quite\n");
			else if (s == SIGINT)
				printf("\n");
			exit_status = 128 + s;
		}
	}
	wait_pids(root->right);
}

int main(int ac, char **av, char **envp)
{
	char *cmd;
	t_main *main;
	int fd;
	(void)ac;
	(void)av;

	main = init(envp);
	if (!main)
		return (0);
	fd = open("tests.txt", O_CREAT| O_RDWR| O_APPEND, 0644);
	exit_status = 0;
	while (1)
	{
		// cmd = readline("mini_sh-1.0$ ");
		cmd = readline("\033[1;33mmini_sh-1.0$ \033[0m");
		if (!cmd)
			break ;
		ft_putendl_fd(cmd, fd);
		if (cmd[0])
		{
			main->ast = formater(cmd, main);
			if(main->ast)
			{
				// printTree(main->ast);
				executer(main->ast, STDIN_FILENO, STDOUT_FILENO, main);
				wait_pids(main->ast);
				destroy_ast_tree(main->ast);
			}
			add_history(cmd);
			free(cmd);
		}
	}
	close(fd);
	return (0);
}
