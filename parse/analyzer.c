/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:25:59 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/16 16:31:10 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	check_opeators(t_lexer *op)
{
	if (!op->next || (op->next->type == CP || (op->next->is_oper
				&& op->next->type != RDIR && op->next->type != HEREDOC
				&& op->next->type != APND)))
		return (ft_error(op->str));
	if (!op->prev || op->prev->type == OP)
		return (ft_error(op->str));
	return (0);
}

int	check_pth(t_lexer *pt)
{
	if (pt->type == OP)
	{
		if (!pt->next || pt->next->type == UNK || pt->next->type == CP)
			return (ft_error(pt->str));
		if (pt->prev && (pt->prev->type == CMD || pt->prev->type == OP))
			return (ft_error(pt->str));
	}
	// else
	// {
	// 	if (pt->next && (pt->next->type == FL || pt->next->type == CMD
	// || pt->next->type == ARGS || pt->next->type == UNK))
	// 		return (ft_error(pt->str), 1);
	// 	if (!pt->prev || (pt->prev->type == UNK || pt->prev->is_oper))
	// 		return (ft_error(pt->str), 1);
	// }
	return (0);
}

int	check_redir(t_lexer *rdir)
{
	if (!rdir->next || (rdir->next->type != UNK && rdir->next->type != FL))
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
		else if (tmp->type == RDIR || tmp->type == APND)
			res += check_redir(tmp);
		else if (tmp->type == OP || tmp->type == CP)
			res += check_pth(tmp);
		else if (tmp->type == UNK && (!ft_strncmp(tmp->str, ";;", \
			ft_strlen(tmp->str))))
			res += ft_error(tmp->str);
		if (res)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
