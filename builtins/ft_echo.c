/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:08:05 by aagouzou          #+#    #+#             */
/*   Updated: 2023/05/25 17:11:14 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	check_new_line(char *arg)
{
	if (!arg)
		return (1);
	else if (!ft_strncmp(arg, "-n", 2))
		return (0);
	return (1);
}

void	ft_echo(t_tree *node)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = check_new_line(node->cmd_args[i]);
	if(!new_line && node->cmd_args[i])
		i++;
	while (node->cmd_args[i])
	{
			printf("%s", node->cmd_args[i]);
		i++;
	}
	if (new_line)
		printf("\n");
}
