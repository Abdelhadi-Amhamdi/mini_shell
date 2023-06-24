/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:28:53 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/23 23:45:34 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	parse_data(char *data)
{
	if (data[0] == '+' || data[0] == '-')
		data++;
	if (check_digits(data))
		return (1);
	return (0);
}

int	is_empty(char *data)
{
	int	index;

	index = 0;
	while (data[index])
	{
		if (data[index] != ' ')
			return (1);
		index++;
	}
	return (0);
}

int	check_args_num(char **args)
{
	int		index;

	index = 1;
	while (args[index])
	{
		if (is_empty(args[index]))
			return (1);
		index++;
	}
	return (0);
}

void	__exit__(int status, t_tree *tree)
{
	destroy_ast_tree(tree);
	exit(status);
}

void	ft_exit(t_tree *cmd_data, t_tree *tree)
{
	char	*data;

	if (!(*cmd_data->args))
	{
		ft_putendl_fd("exit", 1);
		__exit__(0, tree);
	}
	data = cmd_data->args[0];
	ft_putendl_fd("exit", 1);
	if (check_args_num(cmd_data->args))
	{
		ft_putendl_fd("mini-sh: exit: too many arguments!", 2);
		g_exit_status = 255;
		__exit__(g_exit_status, tree);
	}
	if (parse_data(data))
	{
		ft_putendl_fd("mini-sh: exit: numeric argument required!", 2);
		g_exit_status = 255;
		__exit__(g_exit_status, tree);
	}
	else
		__exit__(g_exit_status = (ft_atoi(data) % 256), tree);
}
