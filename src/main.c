
#include "../includes/mini_shell.h"

char	*print_prompt(void)
{
	char	*path;
	char	*data;
	int		i;

	path = getcwd(NULL, 0);
    i = ft_strlen(path) - 1;
	while (i > 0 && path[i] && path[i - 1] != '/')
        i--;
	data = ft_strjoin("\033[0;36m\e[1m",path + i);
	free (path);
	path = NULL;
	path = ft_strjoin(data, " $: \e[m\033[0m");
	free (data);
	data = NULL;
	data = readline(path);
	free (path);
	path = NULL;
	return (data);
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

void executer(t_tree *root)
{
	if (!root)
		return ;
	if (root->type == CMD)
		run_cmd(root);
	else if (root->type == PIPE)
		run_pipeline(root, 0, 1);
	else if (root->type == RDIR)
		run_rdir(root);
}

int main(int ac, char **av, char **envp)
{
	t_app *app;

	(void)ac;
	(void)av;
	app = malloc(sizeof(t_app));
	if (!app)
		return (0);
	app->env_list = get_env_vars(envp);
	while (1)
	{
		clean_data(app);
		app->cmd = NULL;
		app->cmd = print_prompt();
		if (!app->cmd)
			exit (1);
		if (app->cmd[0])
		{
			app->ast_tree = formater(app);
			if (!app->ast_tree)
				return (0);
			executer(app->ast_tree);
			add_history(app->cmd);
			free(app->cmd);
		}
	}
	return (0);
}