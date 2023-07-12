/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:25:59 by aagouzou          #+#    #+#             */
/*   Updated: 2023/07/12 18:42:09 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	check_opeators(t_lexer *op)
{
	if (!op->next || (op->next->type == CP || (op->next->is_oper
				&& op->next->type != RDIR && op->next->type != HEREDOC
				&& op->next->type != APND)))
		return (ft_error(op->str));
	if ((!op->prev && op->type != HEREDOC) || op->prev->type == OP)
		return (ft_error(op->str));
	return (0);
}

int	check_pth(t_lexer *pt)
{
	if (pt->type == OP)
	{
		if (!pt->next || pt->next->type == UNK || pt->next->type == CP)
			return (ft_error(pt->str));
		if (pt->prev && (!pt->prev->is_oper && pt->prev->type != OP))
			return (ft_error(pt->str));
	}
	else
	{
		if (!pt->prev || (pt->prev && pt->prev->is_oper))
			return (ft_error(pt->str), 1);
		if (pt->next && !pt->next->is_oper && pt->next->type != CP)
			return (ft_error(pt->str), 1);
	}
	return (0);
}

int	check_redir(t_lexer *rdir)
{
	if (!rdir->next || rdir->next->type == PIPE || rdir->next->type \
	== RDIR || rdir->next->type == APND || rdir->next->type == AND || \
	rdir->next->type == OR || rdir->next->type == OP || rdir->next->type \
	== CP || rdir->next->type == HEREDOC)
		return (ft_error(rdir->str));
	return (0);
}

int	syntax_analyzer(t_lexer *list)
{
	t_lexer	*tmp;
	int		res;

	tmp = list;
	res = 0;
	if (!list)
		return (1);
	while (tmp)
	{
		if (tmp->is_oper && tmp->type != RDIR && tmp->type != APND
			&& tmp->type != HEREDOC)
			res += check_opeators(tmp);
		else if (tmp->type == RDIR || tmp->type == APND || tmp->type == HEREDOC)
			res += check_redir(tmp);
		else if (tmp->type == OP || tmp->type == CP)
			res += check_pth(tmp);
		else if (tmp->type == UNK && *tmp->str && (!ft_strncmp(tmp->str, ";;", \
			ft_strlen(tmp->str))))
			res += ft_error(tmp->str);
		if (res)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_pths(t_lexer *list)
{
	int	op;
	int	cp;

	op = 0;
	cp = 0;
	while (list)
	{
		if (list->type == OP)
			op++;
		else if (list->type == CP)
			cp++;
		list = list->next;
		if (op - cp < 0)
			break ;
	}
	if (op - cp != 0)
		return (ft_putendl_fd(PARENTICIES_ERROR_MSG, 2), 1);
	return (0);
}
