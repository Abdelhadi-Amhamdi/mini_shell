/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/29 17:42:22 by aamhamdi         ###   ########.fr       */
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
	if (!op->next || (op->next->type == CP || op->next->type == UNK || \
	(op->next->is_oper && op->next->type != RDIR && op->next->type != HEREDOC && op->next->type != APND)))
		return (ft_error(op->str));
	if (!op->prev ||op->prev->type == OP)
		return (ft_error(op->str));
	return (0);
}

int	check_pth(t_lexer *pt)
{
	if (pt->type == OP)
	{
		if (!pt->next || pt->next->type == UNK || pt->next->type == CP)
			return (ft_error(pt->str));
		if (pt->prev && pt->prev->type == OP)
			return (1);
	}
	// else
	// {
	// 	if (pt->next && (pt->next->type == FL || pt->next->type == CMD || pt->next->type == ARGS || pt->next->type == UNK))
	// 		return (ft_error(pt->str), 1);
	// 	if (!pt->prev || (pt->prev->type == UNK || pt->prev->is_oper))
	// 		return (ft_error(pt->str), 1);
	// }
	return (0);
}

int	check_redir(t_lexer *rdir)
{
	if (!rdir->next || (rdir->next->type != UNK  && rdir->next->type != FL))
		return (ft_error(rdir->str));	
	return (0);
}

void print_error(char *str)
{
	ft_putstr_fd("min-sh: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
}

int	syntax_analyzer(t_lexer *list)
{
	t_lexer	*tmp;
	int		res;

	tmp = list;
	res = 0;
	if (tmp->type == UNK)
		return (print_error(tmp->str), 1);
	while (tmp)
	{
		if (tmp->is_oper && tmp->type != RDIR && tmp->type != APND && tmp->type != HEREDOC)
			res += check_opeators(tmp);
		else if (tmp->type == RDIR || tmp->type == APND || tmp->type == HEREDOC)
			res += check_redir(tmp);
		else if (tmp->type == OP || tmp->type == CP)
			res += check_pth(tmp);
		else if (tmp->type == UNK && (!ft_strncmp(tmp->str, ";;", ft_strlen(tmp->str))))
				res += ft_error(tmp->str);
		if (res)
			return (1);
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
	char *path;
	char *cnd;
	// t_lexer *last;
	// t_lexer *new_list;
	// char *data;
	// char **tabs;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == WILDCARD)
		{
			int index = ft_last_char_search(tmp->str, '/') + 1;
			if (!index || tmp->str[index] == '*')
				index = ft_char_search(tmp->str, '*');
			if (index)
			{
				path = ft_substr(tmp->str, 0, index);
				cnd = ft_substr(tmp->str, index, (ft_strlen(tmp->str) - index));
			}
			else
			{
				path = ft_strdup("./");
				cnd = ft_strdup(tmp->str);
			}
			// data = wildcard(path, cnd);
			// tabs = ft_split(data, ' ');
			// new_list = create_list(tabs);
			// last = get_last_token(new_list);
			// last->next = tmp->next;
			// tmp->prev->next = new_list;
			// tabs = NULL;
			// data = NULL;
			printf("%s path -- %s cnd\n", path, cnd);
			// printf("%s\n", data);
		}
		tmp = tmp->next;
	}
}

int	ft_expander(t_lexer *list, t_env *env)
{
	(void)env;
	// char *data;
	if (syntax_analyzer(list))
		return (1);
	// ft_expand_vars(&list, env);
	
	ft_expand_wildcards(&list);
	// data = wildcard(NULL);
	// printf("%s\n", data);
	return (0);
}
