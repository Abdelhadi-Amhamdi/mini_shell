
#include "../includes/mini_shell.h"
void run_pipeline(t_tree *pipe_node, int in, int out);

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

void exec_cmd(t_tree *node, int p1, int p2, int std, int old)
{
	pid_t pid;
	pid = fork();
	if (!pid)
	{
		dup2(p2, std);
		close(p2);
		if (old != -1)
			dup2(old, 1);
		close(p1);
		execve(node->cmd_args[0], node->cmd_args, NULL);
	}
}

void run_pipe(t_tree *cmd, int *pipe,int in, int out, int side)
{
	int		std_file;
	int		used_end;
	int		unused_end;
	int		old;
	
	used_end = in;
	unused_end = pipe[1];
	std_file = STDIN_FILENO;
	old = out;
	if (side == 1)
	{
		used_end = out;
		unused_end = pipe[0];
		std_file = STDOUT_FILENO;
		old = -1;
	}
	if (cmd->type == PIPE)
		run_pipeline(cmd, in, used_end);
	else
		exec_cmd(cmd, unused_end, used_end, std_file, old);
}

void run_pipeline(t_tree *pipe_node, int in, int out)
{
	int fds[2];

	pipe(fds);
	run_pipe(pipe_node->left, fds, in, fds[1], 1);
	run_pipe(pipe_node->right, fds, fds[0], out,  2);
	close(fds[1]);
	close(fds[0]);
	wait(NULL);
	wait(NULL);
}

void run_cmd(t_tree *cmd)
{
	pid_t pid;

	pid = fork();
	if (!pid)
		execve(cmd->cmd_args[0], cmd->cmd_args, NULL);
	wait(NULL);
}

void run_rdir(t_tree *node)
{
	int file_fd;

	unlink(node->right->str);
	file_fd = open(node->right->str, O_CREAT | O_RDWR, 0644);
	if (file_fd == -1)
	{
		printf("error in open\n");
		return ;
	}
	if (node->left->type == PIPE)
		run_pipeline(node->left, 0, file_fd);
	else
	{
		exec_cmd(node->left, -1, file_fd, 1, -1);
		wait(NULL);
	}
	close(file_fd);
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
			// print_ast(app->ast_tree);
			// puts("");
			executer(app->ast_tree);
			add_history(app->cmd);
			free(app->cmd);
		}
	}
	return (0);
}