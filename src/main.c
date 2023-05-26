
#include "../includes/mini_shell.h"
#include <sys/types.h>
#include <sys/wait.h>
# include <signal.h>

t_app *app;

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
		return (-1);
	if (root->type == CMD)
		return (run_cmd(root, &env));
	else if (root->type == PIPE)
		return (run_pipeline(root, 0, 1));
	else if (root->type == RDIR || root->type == APND)
		return (run_rdir(root));
	else if (root->type == HEREDOC)
		return (herdoc(root->right->str, app));
	else if (root->type == AND || root->type == OR)
		return (run_connectors(root));
	return (-1);
}

void ft_free_heredoc_list(t_h_list **list)
{
	t_h_list *tmp;
	t_h_list *next;

	tmp = *list;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*list = NULL;
}

void test(int type)
{

	if (type == SIGINT)
	{
		if (app->lexer_list)
			ft_free_lexer_list(&app->lexer_list);
		if (app->parser_list)
			ft_free_parser_list(&app->parser_list);
		free(app->cmd);
		// destroy the tree;
		ft_free_heredoc_list(&app->herdoc_list);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
	}
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
	signal(SIGINT, test);
	signal(SIGQUIT, SIG_IGN);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
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
				app->status = executer(app->ast_tree, app->env_list);
				// destroy tree;
			}
			add_history(app->cmd);
			free(app->cmd);
		}
	}
	// clean all;
	return (0);
}