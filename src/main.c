
#include "../includes/mini_shell.h"
#include <sys/types.h>
#include <sys/wait.h>

void clean_data(t_app *app)
{
	app->ast_tree = NULL;
	app->cmd = NULL;
	app->lexer_list = NULL;
	app->parser_list = NULL;
	app->in = 0;
	app->out = 1;
}

void print_ast(t_tree *root)
{
	if (!root)
		return ;
	printf("%s ", root->str);
	print_ast(root->left);
	print_ast(root->right);
}

void	exec_builtin(t_tree	*cmd, t_env	**env)
{
	if(!ft_strncmp(cmd->str, "cd", 2))
		ft_cd(*env,cmd);
	else if(!ft_strncmp(cmd->str, "env", 3))
		ft_env(*env);
	else if ( !ft_strncmp(cmd->str, "unset", 6))
		*env = ft_unset(cmd, *env);
	else if (!ft_strncmp(cmd->str, "export", 6))
		ft_export(cmd, env);
	else if (!ft_strncmp(cmd->str, "echo", 5))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd->str, "pwd", 3))
		ft_pwd();
	// else if (!ft_strncmp(cmd->str, "exit", 5))
	// 	ft_exit();
}

int executer(t_tree *root, t_env *env)
{
	if (!root)
		return (-11);
	if (root->type == CMD)
		return (run_cmd(root, &env));
	else if (root->type == PIPE)
		return (run_pipeline(root, 0, 1));
	else if (root->type == RDIR || root->type == APND)
		run_rdir(root);
	else if (root->type == HEREDOC)
		herdoc(root->right->str);
	else if (root->type == AND || root->type == OR)
		return (run_connectors(root));
	return (-11);
}

void test(int sigtype)
{
	if (sigtype == SIGINT)
	{
		int s = 0;
		printf("%d\n", WEXITSTATUS(s));
		// rl_on_new_line();
        // rl_replace_line("", 0);
        // rl_redisplay();
	}
}

int main(int ac, char **av, char **envp)
{
	t_app *app;

	(void)ac;
	(void)av;
	app = malloc(sizeof(t_app));
	if (!app)
		return (0);
	// signal(SIGINT, test);
	app->env_list = get_env_vars(envp);
	while (1)
	{
		clean_data(app);
		app->cmd = NULL;
		app->cmd = readline("mini_sh-1.0$ ");
		if (!app->cmd)
			exit (1);
		if (app->cmd[0])
		{
			app->ast_tree = formater(app);
			if(app->ast_tree)
				executer(app->ast_tree, app->env_list);
			// printTree(app->ast_tree);
			add_history(app->cmd);
			free(app->cmd);
		}
	}
	return (0);
}