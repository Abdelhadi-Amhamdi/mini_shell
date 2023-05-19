/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/19 14:23:38 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*expand(char *var, t_env *envp)
{
	int	index;

	index = 0;
	while (envp)
	{
		if (!ft_strncmp(var, envp->key, ft_strlen(envp->key)))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

void	ft_expand_vars(t_lexer **list, t_env *envp)
{
	t_lexer	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == VAR && tmp->str[0] != '\'')
		{
			while (*(tmp->str) != '$')
				tmp->str = tmp->str + 1;
			tmp->str = expand(tmp->str + 1, envp);
		}
		tmp = tmp->next;
	}
}

#define _ERR_MSG "shell : parse error near"


void	ft_error(char *str)
{
	printf("%s `%s'\n", _ERR_MSG, str);
}

int	check_opeators(t_lexer *op)
{
	if (!op->next || (op->next->type == CP || op->next->type == SQ \
	|| op->next->type == DQ || (op->next->is_oper && op->next->type != RDIR)))
		return (ft_error(op->str), 1);
	if (op->prev && (op->prev->type == OP || op->prev->type == SQ \
	|| op->prev->type == DQ || op->prev->is_oper))
		return (ft_error(op->str), 1);
	return (0);
}

int	check_pth(t_lexer *pt)
{
	if (pt->type == OP)
	{
		if (!pt->next || (pt->next->is_oper || pt->next->type == SQ \
		|| pt->next->type == DQ || pt->next->type == UNK))
			return (ft_error(pt->str), 1);
		if (pt->prev->type == CMD || pt->prev->type == RDIR \
		|| pt->prev->type == UNK)
			return (ft_error(pt->str), 1);
	}
	else
	{
		if (pt->next->type == FL || pt->next->type == CMD \
		|| pt->next->type == ARGS || pt->next->type == UNK)
			return (ft_error(pt->str), 1);
		if (!pt->prev || (pt->prev->type == SQ || pt->prev->type == DQ \
		|| pt->prev->type == UNK || pt->next->is_oper))
			return (ft_error(pt->str), 1);
	}
	return (0);
}

int	check_redir(t_lexer *rdir)
{
	if (!rdir->next || (rdir->next->type != UNK  && rdir->next->type != FL))
		return (ft_error(rdir->str), 1);	
	return (0);
}

int	syntax_analyzer(t_lexer *list)
{
	t_lexer	*tmp;
	int		res;

	tmp = list;
	res = 0;
	while (tmp)
	{
		if (tmp->is_oper && tmp->type != RDIR)
			res += check_opeators(tmp);
		else if (tmp->type == OP || tmp->type == CP)
			res += check_pth(tmp);
		else if (tmp->type == RDIR)
			res += check_redir(tmp);
		if (!ft_strncmp(tmp->str, ";;", ft_strlen(tmp->str)))
			res++;
		if (res)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_qoutes(t_lexer *list)
{
	t_lexer	*tmp;
	char	current;
	char	*data;
	int		index;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == DQ || tmp->type == SQ)
		{
			index = 0;
			data = tmp->str;
			current = data[index];
			while (data[++index] && data[index] != current);
			if (!data[index])
				return (ft_putendl_fd("Syntax Error", 2), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_expander(t_lexer *list, t_env *env)
{
	if (check_qoutes(list))
		return (1);
	if (syntax_analyzer(list))
		return (1);
	ft_expand_vars(&list, env);
	//check phts
	// clean list;
	return (0);
}
