/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:55:24 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/07 17:48:56 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	parser_helper(t_parser *list)
{
	t_parser	*tmp;
	int			single_qutes;
	int			double_qutes;
	t_type		current;

	tmp = list;
	single_qutes = 0;
	double_qutes = 0;
	while (tmp)
	{
		if ((tmp->type == SQ || tmp->type == DQ) \
		&& (!(single_qutes % 2) && !(double_qutes % 2)))
			current = tmp->type;
		if (tmp->type == SQ && tmp->type == current)
			single_qutes++;
		else if (tmp->type == DQ && tmp->type == current)
			double_qutes++;
		tmp = tmp->next;
	}
	if (single_qutes % 2 || double_qutes % 2)
		return (printf("Error Qutes not closed!\n"), 1);
	tmp = list;
	if (tmp->type != CMD && tmp->type != TOKEN)
		return (printf("Error %s : not found\n", tmp->str), 1);
	return (0);
}

void	exec_builtins(t_parser *cmd, t_env *env)
{
	if (!ft_strncmp(cmd->str, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd->str, "cd", 2))
		ft_cd(env, cmd->next);
	else if (!ft_strncmp(cmd->str, "echo", 4))
		ft_echo(cmd->next);
}

int ft_calc(t_parser *list)
{
	int count;

	count = 0;
	while (list && (list->type == UNK || list->type == ARGS))
	{
		count++;
		list = list->next;
	}
	return (count);
}

void execc(t_parser *list)
{
	char **cmd;
	int	index;
	t_parser *tmp;
	int size;

	index = 0;
	size = ft_calc(list->next);
	cmd = (char **)malloc(sizeof(char *) * (size + 1));
	cmd[index] = list->str;
	tmp = list->next;
	if (tmp && (tmp->type == UNK || tmp->type == ARGS))
	{
		index++;
		cmd[index] = tmp->str;
		tmp = tmp->next;
	}
	cmd[++index] = NULL;
	index = 0;
	// while (cmd[index])
	// {
	// 	printf("%s ", cmd[index]);
	// 	index++;
	// }
	// puts("");
	execve(list->path, cmd, NULL);
}

void	exec_any(t_parser *args_list, t_env *env_list)
{
	// int		fd[2];
	pid_t	pid;

	(void)env_list;
	// pipe(fd);
	while (args_list)
	{
		if (args_list->type == CMD)
		{
			pid = fork();
			if (pid == 0)
			{
				// dup2(fd[1], STDOUT_FILENO);
				execc(args_list);
			}
			// close(fd[1]);
			waitpid(pid, NULL, 0);
		}
		args_list = args_list->next;
	}
	
}

void	exec_cmd(t_parser *list, t_env *env)
{
	t_parser	*tmp;

	tmp = list;
	if (tmp->is_builtin)
		exec_builtins(tmp, env);
	else
		exec_any(tmp, env);
}

int	calc_pipes(t_parser *list)
{
	t_parser	*tmp;
	int			count;

	tmp = list;
	count = 0;
	while (tmp)
	{
		if (tmp->type == TOKEN && tmp->str[0] == '|')
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	executer(t_parser *cmds_list, t_env *env_list)
{
	t_parser	*tmp;
	int			pipes;

	tmp = cmds_list;
	pipes = calc_pipes(tmp);
	if (parser_helper(cmds_list))
		return (1);
	exec_cmd(tmp, env_list);
	return (0);
}