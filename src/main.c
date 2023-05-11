
#include "../includes/mini_shell.h"

char	*print_prompt(void)
{
	char	*p;
	int		i;

	p = getcwd(NULL, 0);
    i = ft_strlen(p) - 1;
	while (i > 0 && p[i] && p[i - 1] != '/')
        i--;
	p = ft_strjoin("\033[0;36m\e[1m",p + i);
	p = ft_strjoin(p, " $: \e[m\033[0m");
	return (readline(p));
}

int main(int ac, char **av, char **envp)
{
	t_env		*env_list;
	t_parser	*parser_list;
	char		*cmd;

	(void)ac;
	(void)av;
	env_list = get_env_vars(envp);
	while (1)
	{
		cmd = NULL;
		cmd = print_prompt();
		if (!cmd)
			exit (1);
		if (cmd && *cmd)
		{
			parser_list = formater(cmd, env_list);
			executer(parser_list, &env_list);
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}