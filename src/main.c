
#include "../includes/mini_shell.h"
#include <sys/types.h>
#include <sys/wait.h>
# include <signal.h>

t_app *app;

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

void print_ast(t_tree *root)
{
	if (!root)
		return ;
	printf("%s ", root->str);
	print_ast(root->left);
	print_ast(root->right);
}

void init(t_app *app, char **env)
{
	app->status = 0;
	app->cmd = NULL;
	app->ast_tree = NULL;
	app->lexer_list = NULL;
	app->parser_list = NULL;
	app->herdoc_list = NULL;
	app->env_list = get_env_vars(env);
	// signal(SIGINT, test);
	// signal(SIGQUIT, SIG_IGN);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	// print_banner();
	app = malloc(sizeof(t_app));
	if (!app)
		return (0);
	init(app, envp);
	while (1)
	{
		clean_data(app);
		app->cmd = readline("mini_sh-1.0$ ");
		if (!app->cmd)
			break ;
		if (app->cmd[0])
		{
			app->ast_tree = formater(app);
			if(app->ast_tree)
			{
				// printTree(app->ast_tree);
				app->status = executer(app->ast_tree, app);
				// destroy tree;
			}
			add_history(app->cmd);
			free(app->cmd);
		}
	}
	// clean all;
	return (0);
}