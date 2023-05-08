/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:22:02 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/08 17:00:17 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_boolean	check_new_line(t_parser *node)
{
	if (!node)
		return (true);
	else if (!ft_strncmp(node->str, "-n", 2))
		return (false);
	return (true);
}

void	ft_echo(t_parser *node)
{
	t_boolean new_line;
	char	q;

	q = '\0';
	new_line = check_new_line(node);
	while(node)
	{
		if(node->str && node->type != SQ && node->type != DQ && node->type != ARGS)
			printf("%s ",node->str);
		// else if(node->type == SQ)
		// 	printf("%s ",node->str);
		node = node->next;
	}
	if(new_line)
		printf("\n");
	// if (q)
	// {
	// 	node = node->next;
	// 	while (node->type != TOKEN &&)
	// 	{
	// 		if (node->type != ARGS)
	// 			ft_putstr_fd(node->str, 1);
	// 		else if (!ft_strncmp(node->str, "-n", 2))
	// 			new_line = false;
	// 		node = node->next;
	// 	}
	// }
	// else
	// 	ft_putstr_fd(node->str, 1);
	// if (new_line)
	// 	ft_putendl_fd("", 1);
}
