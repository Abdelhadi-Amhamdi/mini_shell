/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/25 20:54:06 by aamhamdi         ###   ########.fr       */
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
		if (pt->prev && (pt->prev->type == CMD || pt->prev->type == RDIR \
		|| pt->prev->type == UNK))
			return (ft_error(pt->str), 1);
	}
	else
	{
		if (pt->next && (pt->next->type == FL || pt->next->type == CMD \
		|| pt->next->type == ARGS || pt->next->type == UNK))
			return (ft_error(pt->str), 1);
		if (!pt->prev || (pt->prev->type == SQ || pt->prev->type == DQ \
		|| pt->prev->type == UNK || pt->prev->is_oper))
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
		else if (tmp->type != EMPTY)
		{
			if (!ft_strncmp(tmp->str, ";;", ft_strlen(tmp->str)))
				res++;
		}
		if (res)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_trim_quotes(t_lexer *node)
{
	t_lexer	*tmp;

	tmp = node;
	if (tmp->type == SQ)
		tmp->str = ft_strtrim(tmp->str, "'");
	else 
		tmp->str = ft_strtrim(tmp->str, "\"");
	if (!tmp->str[0])
	{
		tmp->str = NULL;
		tmp->type = EMPTY;
	}
	else
		tmp->type = ARGS;
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
			ft_trim_quotes(tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_lexer *create_list(char **tabs)
{
	int index = 0;
	t_lexer *list;
	t_lexer *new_node;

	list = NULL;
	while (tabs[index])
	{
		new_node = create_token(tabs[index], 0, NULL);
		add_token_to_end(&list, new_node);
		index++;
	}
	return (list);
}

t_lexer *get_last_token(t_lexer *list)
{
	while (list->next)
		list = list->next;
	return  (list);
}

void ft_expand_wildcards(t_lexer **list)
{
	t_lexer *tmp;
	t_lexer *last;
	t_lexer *new_list;
	char *data;
	char **tabs;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == WILDCARD)
		{
			data = wildcard(tmp);
			tabs = ft_split(data, ' ');
			new_list = create_list(tabs);
			last = get_last_token(new_list);
			last->next = tmp->next;
			tmp->prev->next = new_list;
			tabs = NULL;
			data = NULL;
		}
		tmp = tmp->next;
	}
}

int check_pths(t_lexer *list)
{
	int op;
	int cp;
	t_lexer *tmp;

	op = 0;
	cp = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == OP)
			op++;
		else if (tmp->type == CP)
			cp++;
		tmp = tmp->next;
	}
	if (!(op % 2) || !(cp % 2))
		return (ft_putendl_fd("Syntax Error", 2), 1);
	return (0);
}

int	ft_expander(t_lexer *list, t_env *env)
{
	if (check_qoutes(list))
		return (1);
	if (syntax_analyzer(list) || check_pths(list))
		return (1);
	ft_expand_vars(&list, env);
	ft_expand_wildcards(&list);
	return (0);
}
