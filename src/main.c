
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

int main(int ac, char **av, char **envp)
{
	t_env		*env_list;
	t_parser	*parser_list;
	char		*cmd;

	(void)ac;
	(void)av;
	env_list = get_env_vars(envp);
	// signal(SIGINT,act);
	while (1)
	{
		cmd = NULL;
		cmd = print_prompt();
		if (!cmd)
			exit (1);
		if (cmd && *cmd)
		{
			parser_list = formater(cmd, env_list);
			// if (parser_list)
			// 	executer(parser_list, &env_list);
			add_history(cmd);
			// rl_on_new_line();
			// free(cmd);
		}

	}
	return (0);
}