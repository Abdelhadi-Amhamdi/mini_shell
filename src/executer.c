/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:55:24 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/05 22:16:43 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	ft_calc_arg(char *str, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == c)
			count++;
		index ++;
	}
	return (count);
}

int	parser_helper(t_parser *list)
{
	t_parser	*tmp;
	int			single_qutes;
	int			double_qutes;

	tmp = list;
	single_qutes = 0;
	double_qutes = 0;
	while (tmp)
	{
		if (tmp->type == SQ)
		{
			single_qutes += ft_calc_arg(tmp->str, tmp->str[0]);
			if (single_qutes == 2)
				double_qutes = 0;
		}
		else if (tmp->type == DQ)
		{
			double_qutes += ft_calc_arg(tmp->str, tmp->str[0]);
			if (double_qutes == 2)
				single_qutes = 0;
		}
		tmp = tmp->next;
	}
	if (single_qutes % 2 || double_qutes % 2)
	{
		printf("%d d --- %d s\n", double_qutes, single_qutes);
		return (printf("Error Qutes not closed!\n"), 1);
	}
	tmp = list;
	if (tmp->type != CMD)
		return (printf("Error %s : not found\n", tmp->str), 1);
	return (0);
}

int	executer(t_parser *cmds_list)
{
	t_parser	*tmp;

	tmp = cmds_list;
	if (parser_helper(cmds_list))
		return (1);
	return (0);
}