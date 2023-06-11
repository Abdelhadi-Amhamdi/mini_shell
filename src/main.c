/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:49:28 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/11 18:44:51 by aamhamdi         ###   ########.fr       */
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

t_app *init(char **env)
{
	t_app *app;

	app = malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->status = 0;
	app->hdoc_fd = -1;
	app->env_list = get_env_vars(env);
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	return (app);
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
			app->status = WEXITSTATUS(status);
	}
	wait_pids(root->right);
}

int main(int ac, char **av, char **envp)
{
	char *cmd;
	t_tree *ast_tree;
	(void)ac;
	(void)av;

	app = init(envp);
	if (!app)
		return (0);
	while (1)
	{
		cmd = readline("\033[1;33mmini_sh-1.0$ \033[0m");
		if (!cmd)
			break ;
		if (cmd[0])
		{
			ast_tree = formater(cmd);
			if(ast_tree)
			{
				// printTree(ast_tree);
				executer(ast_tree, STDIN_FILENO, STDOUT_FILENO);
				wait_pids(ast_tree);
				destroy_ast_tree(ast_tree);
			}
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}
