
#include "../includes/mini_shell.h"

// int	parser_helper(t_parser *list)
// {
// 	t_parser	*tmp;
// 	int			single_qutes;
// 	int			double_qutes;
// 	t_type		current;

// 	tmp = list;
// 	single_qutes = 0;
// 	double_qutes = 0;
// 	while (tmp)
// 	{
// 		if ((tmp->type == SQ || tmp->type == DQ) \
// 		&& (!(single_qutes % 2) && !(double_qutes % 2)))
// 			current = tmp->type;
// 		if (tmp->type == SQ && tmp->type == current)
// 			single_qutes++;
// 		else if (tmp->type == DQ && tmp->type == current)
// 			double_qutes++;
// 		tmp = tmp->next;
// 	}
// 	if (single_qutes % 2 || double_qutes % 2)
// 		return (printf("Error Qutes not closed!\n"), 1);
// 	tmp = list;
// 	if (tmp->type != CMD && tmp->type != TOKEN)
// 		return (printf("Error %s : not found\n", tmp->str), 1);
// 	return (0);
// }

// // void	exec_builtins(t_parser *cmd, t_env **env)
// // {
// // 	if (!ft_strncmp(cmd->str, "pwd", 3))
// // 		ft_pwd();
// // 	else if (!ft_strncmp(cmd->str, "cd", 2))
// // 		ft_cd(*env, cmd->next);
// // 	else if (!ft_strncmp(cmd->str, "echo", 4))
// // 		ft_echo(cmd->next);
// // 	else if (!ft_strncmp(cmd->str, "export", 6))
// // 	{
// // 		// puts("export");
// // 		// print_parser_list(cmd);
// // 		ft_export(cmd, env);
// // 	}
// // 	else if (!ft_strncmp(cmd->str, "env", 3))
// // 		ft_env(*env);
// // 	else if (!ft_strncmp(cmd->str, "unset", 5))
// // 		ft_unset(cmd ,*env);
// // }

// int ft_calc(t_parser *list)
// {
// 	int count;

// 	count = 0;
// 	while (list && (list->type == UNK || list->type == ARGS))
// 	{
// 		count++;
// 		list = list->next;
// 	}
// 	return (count);
// }

// void execc(t_parser *list)
// {
// 	char **cmd;
// 	int	index;
// 	t_parser *tmp;
// 	int size;

// 	index = 0;
// 	size = ft_calc(list->next);
// 	cmd = (char **)malloc(sizeof(char *) * (size + 1));
// 	cmd[index] = list->str;
// 	tmp = list->next;
// 	if (tmp && (tmp->type == UNK || tmp->type == ARGS))
// 	{
// 		index++;
// 		cmd[index] = tmp->str;
// 		tmp = tmp->next;
// 	}
// 	cmd[++index] = NULL;
// 	index = 0;
// 	// while (cmd[index])
// 	// {
// 	// 	printf("%s ", cmd[index]);
// 	// 	index++;
// 	// }
// 	execve(list->path, cmd, NULL);
// }

// t_parser *get_next_item(t_parser *list)
// {
// 	while (list)
// 	{
// 		if (list->type == TOKEN)
// 			return 	list;
// 		list = list->next;
// 	}
// 	return (NULL);
// }

// void	exec_cmd(t_parser *list, t_env *env)
// {
// 	if (tmp->is_builtin)
// 		exec_builtins(tmp, env);
// 	else
// 		exec_any(tmp, env);
// }

// int	calc_pipes(t_parser *list)
// {
// 	t_parser	*tmp;
// 	int			count;

// 	tmp = list;
// 	count = 0;
// 	while (tmp->next)
// 	{
// 		if (tmp->type == TOKEN && tmp->str[0] == '|')
// 			count++;
// 		tmp = tmp->next;
// 	}
// 	return (count);
// }

// void	exec_cmd(t_parser *list, t_env *env)
// {
// 	t_parser	*tmp;
// 	t_parser	*next;
// 	pid_t		pid;
// 	int			fd[2];
// 	int			pipes;

// 	tmp = list;
// 	pipes = 0;
// 	while (tmp)
// 	{
// 		next = get_next_item(tmp->next);
// 		if (next && next->str[0] == '|')
// 		{
// 			pipe(fd);
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				close(fd[0]);
// 				dup2(fd[1], STDOUT_FILENO);
// 				close(fd[1]);
// 				exec__(tmp, env);
// 			}
// 			else
// 			{
// 				close(fd[1]);
// 				waitpid(pid, NULL, 0);
// 				dup2(fd[0], STDIN_FILENO);
// 			}
// 			tmp = next->next;
// 			pipes++;
// 		}
// 		// else if (next && next->str[0] == '>')
// 		// {
// 		// 	pid = fork();
// 		// 	if (pid == 0)
// 		// 	{
// 		// 		int f = open(next->next->str, O_RDWR | O_CREAT, 777);
// 		// 		dup2(f, STDOUT_FILENO);
// 		// 		close(f);
// 		// 		exec__(tmp, env);
// 		// 	}
// 		// 	tmp = NULL;
// 		// }
// 		else
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				if (pipes)
// 				{
// 					close(fd[1]);
// 					close(fd[0]);
// 				}
// 				exec__(tmp, env);
// 			}
// 			else
// 			{
// 				if (pipes)
// 				{
// 					close(fd[1]);
// 					close(fd[0]);
// 				}
// 				waitpid(pid, NULL, 0);
// 				dup2(STDIN_FILENO, fd[0]);
// 			}
// 			tmp = NULL;
// 		}
// 	}
// }



// int	executer(t_parser *cmds_list, t_env **env_list)
// {
// 	t_parser	*tmp;

// 	tmp = cmds_list;
// 	if (parser_helper(cmds_list))
// 		return (1);
// 	// puts("hooo");
// 	exec_cmd(tmp, env_list);
// 	return (0);
// }





























	// pipe(fd);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	close(fd[0]);
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[1]);
	// 	exec__(tmp, env);
	// }
	// else
	// {
	// 	close(fd[1]);
	// 	wait(NULL);
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// }
	// next = get_next_item(tmp);
    // tmp = next->next;
	// pipe(fd);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	close(fd[0]);
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[1]);
	// 	exec__(tmp, env);
	// }
	// else
	// {
	// 	close(fd[1]);
	// 	wait(NULL);
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// }
	// next = get_next_item(tmp);
    // tmp = next->next;
	// pid = fork();
	// if (pid == 0)
	// {
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	exec__(tmp , env);
	// }
	// else
	// {
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	wait(NULL);
	// }