/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:08:05 by aagouzou          #+#    #+#             */
/*   Updated: 2023/05/24 13:08:36 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_boolean	check_new_line(t_parser *node)
{
	if (!node)
		return (true);
	else
	{
		if(node->str)
			if (!ft_strncmp(node->str, "-n", 2))
				return (false);
	}
	return (true);
}

void	ft_echo(t_parser *node)
{
	t_boolean new_line;

	printf("i was in here\n");
	new_line = check_new_line(node);
	while(node)
	{
		if (node->type == PIPE)
			break ;
		if((node->prev->type == DQ && node->type == SQ) || (node->prev->type == SQ && node->type == DQ))
			printf("%c",'\'');
		if(node->str && node->type != SQ && node->type != DQ && node->type != ARGS)
			printf("%s",node->str);
		node = node->next;
		if(node && node->type != SQ && node->type != DQ && node->prev->type != SQ && node->prev->type != DQ)
			printf(" ");
	}
	if(new_line)
		printf("\n");
}
