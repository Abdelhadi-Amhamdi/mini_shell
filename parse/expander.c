/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/19 14:10:40 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*expand(char *var, t_env *envp)
{
	int	index;

	index = 0;
	while (envp)
	{
		if (!ft_strncmp(var, envp->key, ft_strlen(envp->key)))// && ft_strlen(envp->key) == ft_strlen(var)
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
				tmp->str = tmp->str+1;
			
			tmp->str = expand(tmp->str+1, envp);
			
		}
		tmp = tmp->next;
	}
}

#define _ERR_MSG "shell : parse error near"

// int check_qoutes(t_lexer *lexer_list)
// {
// 	t_lexer		*tmp;
// 	int			single_qutes;
// 	int			double_qutes;
// 	t_type		current;

// 	single_qutes = 0;
// 	double_qutes = 0;
// 	tmp = lexer_list;
// 	while (tmp)
// 	{
// 		if ((tmp->type == SQ || tmp->type == DQ) \
// 		&& (!(single_qutes % 2) && !(double_qutes % 2)))
// 			current = tmp->type;
// 		if (tmp->type == SQ && tmp->type == current)
// 			single_qutes++;
// 		else if (tmp->type == DQ && tmp->type == current)
// 			double_qutes++;
// 		tmp = tmp->next;
// 	}
// 	if (single_qutes % 2 || double_qutes % 2)
// 		return (printf("Error Qutes not closed!\n"), 1);
// 	return (0);
// }

void ft_error(char *str)
{
	printf("%s `%s'\n", _ERR_MSG, str);
}

int check_opeators(t_lexer *op)
{
	if (!op->next || (op->next->type == CP || op->next->type == SQ \
	|| op->next->type == DQ || (op->next->is_oper && op->next->type != RDIR)))
		return (ft_error(op->str), 1);
	if (op->prev && (op->prev->type == OP || op->prev->type == SQ \
	|| op->prev->type == DQ || op->prev->is_oper))
		return (ft_error(op->str), 1);
	return (0);
}

int check_pth(t_lexer *pt)
{
	if (pt->type == OP)
	{
		if (!pt->next || (pt->next->is_oper || pt->next->type == SQ \
		|| pt->next->type == DQ || pt->next->type == UNK))
			return (ft_error(pt->str), 1);
		if (pt->prev->type == CMD || pt->prev->type == RDIR \
		||  pt->prev->type == UNK)
			return (ft_error(pt->str), 1);
	}
	else
	{
		if (pt->next->type == FL || pt->next->type == CMD \
		|| pt->next->type == ARGS || pt->next->type == UNK)
			return (ft_error(pt->str), 1);
		if (!pt->prev || (pt->prev->type == SQ || pt->prev->type == DQ \
		||  pt->prev->type == UNK || pt->next->is_oper))
			return (ft_error(pt->str), 1);
	}
	return (0);
}

int check_redir(t_lexer *rdir)
{
	if (!rdir->next || (rdir->next->type != UNK  && rdir->next->type != FL))
		return (ft_error(rdir->str), 1);	
	return (0);
}

int syntax_analyzer(t_lexer *list)
{
	t_lexer *tmp;
	int res;

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
			return 1;
		tmp = tmp->next;
	}
	return (0);
}

int is_closed(char *str)
{
	char current;
	int index;
	
	current = str[0];
	index = 1;
	while (str[index])
	{
		if (str[index] == current)
			return (1);
		index++;
	}
	return (0);
}

void handle_quotes(t_lexer **list)
{
	t_lexer *tmp;
	t_lexer *tmp1;
	
	tmp = *list;
	tmp1 = NULL;
	t_type current;
	while (tmp)
	{
		if ((tmp->type == SQ || tmp->type == DQ) && !is_closed(tmp->str))
		{
			current = tmp->type;
			tmp1 = tmp->next;
			while (tmp1)
			{
				tmp->str = ft_strjoin(tmp->str, tmp1->str);
				if (tmp1->type != SQ && tmp1->type != DQ)
					tmp->type = tmp1->type;
				if (tmp1->type == current || is_closed(tmp->str))
					break ;
				tmp1 = tmp1->next;	
			}
			tmp->next = tmp1->next;
		}
		tmp = tmp->next;
	}
}

int is_empty_args(t_lexer *node)
{
	int index;
	char *str;

	index = 1;
	str = node->str;
	while (str[index])
	{
		if (str[index] != '"')
			return (1);
		index++;
	}
	return (0);
}

void create_blocks_helper(t_lexer **list)
{
	t_lexer *tmp;
	t_lexer *tmp1;
	
	tmp = *list;
	tmp1 = NULL;
	while (tmp)
	{
		if (!tmp->is_oper && tmp->type != CMD && is_empty_args(tmp))
		{
			tmp1 = tmp->next;
			while (tmp1 && !tmp1->is_oper && tmp1->type != CMD)
			{
				// if (is_empty_args(tmp1))
				tmp->str = ft_strjoin(tmp->str, tmp1->str);
				tmp1 = tmp1->next;
			}
			tmp->next = tmp1;
		}
		tmp = tmp->next;
	}
}

void group_by_qoutes(t_lexer **list)
{
	t_lexer *tmp;
	t_lexer *tmp1;

	tmp = *list;
	tmp1 = NULL;
	handle_quotes(list);
	// create_blocks_helper(list);
}

int check_qoutes(t_lexer *list)
{
	t_lexer *tmp;
	char current;
	char *data;
	int index;

	tmp = list;
	// puts(hello);
	while (tmp)
	{
		if (tmp->type == DQ || tmp->type == SQ)
		{
			index = 0;
			data = tmp->str;
			current = data[index];
			while (data[++index] && data[index] != current);
			if (!data[index])
			{
				printf("Syntax Error\n");
				return (1);	
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

t_lexer	*ft_expander(t_lexer *list, t_env *env)
{
	(void)env;
	// check quotes;
	if (check_qoutes(list))
		return (NULL);

	// syntax analyzer
	// if (syntax_analyzer(list))
	// 	return (NULL);
	
	// create blocks
	// group_by_qoutes(&list);
	
	//check phts
		
	// expand vars
	// ft_expand_vars(&list, env);
	
	// clean list;
	
	return (list);
}
