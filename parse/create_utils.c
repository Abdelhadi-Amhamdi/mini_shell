/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:31:43 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/23 19:32:41 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	contain_only_qs(t_lexer *tmp)
{
	int	i;

	i = 0;
	if (!(*tmp->str))
		return (1);
	if (tmp->type == SQ)
	{
		while (tmp->str[i])
		{
			if (tmp->str[i] != '\'')
				return (1);
			i++;
		}
	}
	else if (tmp->type == DQ)
	{
		while (tmp->str[i])
		{
			if (tmp->str[i] != '"')
				return (1);
			i++;
		}
	}
	return (0);
}

void	is_printable_sp(t_lexer *tmp)
{
	if (tmp->type == SQ && all_inside_is_sp(tmp) && contain_only_qs(tmp))
		tmp->id = PREINTABLE_SPACE;
	else if (tmp->type == DQ && all_inside_is_sp(tmp) && contain_only_qs(tmp))
		tmp->id = PREINTABLE_SPACE;
}

void	will_remove_sp(t_lexer *tmp)
{
	if (contain_spaces(tmp->str))
		tmp->id = DONT_REMOVESP;
}