/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:22:02 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/07 13:07:32 by aamhamdi         ###   ########.fr       */
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
	char	q;
	t_boolean new_line;

	q = '\0';
	new_line = check_new_line(node);
	if (!node)
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	if (node->type == SQ || node->type == DQ)
		q = node->str[0];
	if (q)
	{
		node = node->next;
		while (node->type != TOKEN)
		{
			if (node->type != ARGS)
				ft_putstr_fd(node->str, 1);
			else if (!ft_strncmp(node->str, "-n", 2))
				new_line = false;
			node = node->next;
		}
	}
	else
		ft_putstr_fd(node->str, 1);
	if (new_line)
		ft_putendl_fd("", 1);
}
