
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

void run_pipe(t_tree *node, int *fds , int out, int side)
{
	t_tree *cmd;
	int file;
	int end;
	int end_close;
	pid_t pid;
	
	(void)out;

	cmd = node->right;
	end = fds[0];
	end_close = fds[1];
	file = STDIN_FILENO;
	if (side == 1)
	{
		cmd = node->left;
		end = fds[1];
		end_close = fds[0];
		file = STDOUT_FILENO;
	}
	pid = fork();
	if (!pid)
	{
		close(end_close);
		dup2(end, file);
		close(end);
		execve(cmd->cmd_args[0], cmd->cmd_args, NULL);
	}
}

void run_pipeline(t_tree *pipe_node, int in, int out)
{
	int fds[2];

	(void)in;
	pipe(fds);
	run_pipe(pipe_node, fds, out, 1);
	run_pipe(pipe_node, fds , out, 2);
	close(fds[1]);
	close(fds[0]);
	wait(NULL);
	wait(NULL);
}

void	exec_builtin(t_tree	*cmd, t_env	*env)
{
	if(!ft_strncmp(cmd->str, "cd", 2))
		ft_cd(env,cmd);
	// else if(!ft_strncmp(cmd->str, "env", 3))
	// 	ft_env(env);
	// else if ( !ft_strncmp(cmd->str, "unset", 6))
	// 	ft_unset(cmd, env);
	// else if (!ft_strncmp(cmd->str, "export", 6))
	// 	ft_export(cmd, env);
	// else if (!ft_strncmp(cmd->str, "echo", 5))
	// 	ft_echo(cmd);
	// else if (!ft_strncmp(cmd->str, "pwd", 3))
	// 	ft_pwd();
	// else if (!ft_strncmp(cmd->str, "exit", 5))
	// 	ft_exit();
}

void run_cmd(t_tree *cmd, t_env	*env)
{
	pid_t pid;

	if(cmd->is_builtin)
	{
		exec_builtin(cmd, env);
		return ;
	}
	pid = fork();
	if (pid == 0)
		execve(cmd->cmd_args[0], cmd->cmd_args, NULL);
	wait(NULL);
}


void executer(t_tree *root, t_env	*env)
{
	if (!root)
		return ;
	if (root->type == CMD)
		run_cmd(root, env);
	else if (root->type == PIPE)
		run_pipeline(root, 0, 1);
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
		// app->cmd = readline("> ");
		if (!app->cmd)
			exit (1);
		if (app->cmd[0])
		{
			app->ast_tree = formater(app);
			// if (!app->ast_tree)
			// 	return (0);
			// print_ast(app->ast_tree);
			// puts("");
			if(app->ast_tree)
				executer(app->ast_tree, app->env_list);
			add_history(app->cmd);
			free(app->cmd);
		}
	}
	return (0);
}