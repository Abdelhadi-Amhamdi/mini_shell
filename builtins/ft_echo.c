/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:08:05 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/10 21:55:03 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/mini_shell.h"

int is_all_space(char *s)
{
	int i;

	i = 0;
	while(s[i])
	{
		if(!is_space(s[i]))
			return (0);
		i++;
	}
	return(1);
}

int	check_new_line(char *arg)
{
	if (!arg)
		return (1);
	else if (!ft_strncmp(arg, "-n", 2))
		return (0);
	return (1);
}

int	ft_echo(t_tree *node)
{
	int	new_line;
	int	i;

	i = 0;
	new_line = check_new_line(node->args[i]);
	while (node->args[i])
	{
		if(is_all_space(node->args[i]))
			printf(" ");
		else
			printf("%s", node->args[i]);
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
