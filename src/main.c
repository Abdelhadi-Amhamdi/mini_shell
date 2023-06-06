/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:49:28 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/06 20:41:31 by aamhamdi         ###   ########.fr       */
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

void sig_int_handler(int sigtype)
{
	if (sigtype == SIGINT)
	{
		if (app->hdoc_fd > 0)
		{
			close(app->hdoc_fd);
			app->hdoc_fd = 0;
			unlink(HEREDOC_FILENAME);
		}
		exit (0);
	}
}

void set_exit_status(int new_status)
{
	app->status = new_status;
}

char *get_exit_status()
{
	return (ft_itoa(app->status >> 8));
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
	root->path = NULL;
	free(root->str);
	free(root);
	root = NULL;
	root = NULL;
	destroy_ast_tree(right);
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
		cmd = readline("mini_sh-1.0$ ");
		if (!cmd)
			break ;
		if (cmd[0])
		{
			ast_tree = formater(cmd);
			if(ast_tree)
			{
				printTree(ast_tree);
				// executer(ast_tree);
				destroy_ast_tree(ast_tree);
			}
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}
