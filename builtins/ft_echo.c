/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:08:05 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/26 11:58:59 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	is_all_space(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!is_space(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_all_n(char *data)
{
	int	index;

	index = 0;
	while (data[index])
	{
		if (data[index] != 'n')
			return (1);
		index++;
	}
	return (0);
}

int	check_new_line(char *arg)
{
	if (!arg)
		return (1);
	else if (arg[0] == '-' && !is_all_n(++arg))
		return (0);
	return (1);
}

int	ft_echo(t_tree *node, int out)
{
	int	new_line;
	int	i;

	i = 0;
	new_line = check_new_line(node->args[i]);
	if (!new_line)
	{
		while (!check_new_line(node->args[i]) || is_all_space(node->args[i]))
			i++;
	}
	while (node->args[i])
	{
		if (*(node->args[i]))
			ft_putstr_fd(node->args[i], out);
		if (node->args[i + 1])
			ft_putchar_fd(' ', out);
		i++;
	}
	if (new_line)
		ft_putendl_fd("", out);
	return (0);
}
