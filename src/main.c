
#include "../includes/mini_shell.h"
#include <sys/types.h>
#include <sys/wait.h>
# include <signal.h>

int exit_status;

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

void clean_data(t_app *app)
{
	app->ast_tree = NULL;
	app->cmd = NULL;
	app->lexer_list = NULL;
	app->parser_list = NULL;
}

// void test()
// {
// 	int fd = open("heredoc_file", O_RDONLY);
// 	printf("%d\n", fd);
// }

void set_exit_status(int new_status)
{
	exit_status = new_status;
	printf("%d\n", exit_status);
}

t_app *init(char **env)
{
	t_app *app;

	app = malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->status = 0;
	app->cmd = NULL;
	app->ast_tree = NULL;
	app->lexer_list = NULL;
	app->parser_list = NULL;
	app->herdoc_list = NULL;
	app->env_list = get_env_vars(env);
	signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_IGN);
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
	free(root->str);
	// ft_free(root->cmd_args);
	free(root);
	root = NULL;
	root = NULL;
	destroy_ast_tree(right);
}

int main(int ac, char **av, char **envp)
{
	t_app	*app;
	(void)ac;
	(void)av;

	app = init(envp);
	if (!app)
		return (0);
	while (1)
	{
		clean_data(app);
		app->cmd = readline("mini_sh-1.0$ ");
		if (!app->cmd)
			break ;
		if (app->cmd[0])
		{
			formater(app);
			if(app->ast_tree)
			{
				// printTree(app->ast_tree);
				executer(app->ast_tree, app);
				destroy_ast_tree(app->ast_tree);
			}
			add_history(app->cmd);
			free(app->cmd);
		}
	}
	return (0);
}