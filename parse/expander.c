/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/31 11:53:26 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*expand(char *var, t_env *envp)
{
	int	index;

	index = 0;
	while (envp)
	{
		if (!ft_strncmp(var, envp->key, ft_strlen(var)))
			return (envp->value);
		envp = envp->next;
	}
	return (ft_strdup(" "));
}
//extarct before command
char *extract_before(char *cmd)
{
	int i;
	int index;
	char *before;
	i = 0;
	while(cmd[i] && cmd[i] != '$')
		i++;
	before = malloc (i + 1);
	if(!before)
		return (NULL);
	index = 0;
	while(cmd[index] && cmd[index] != '$')
	{
		before[index] = cmd[index];
		index++;
	}
	before[index] = '\0';
	return (before);
}
//extract variable to expland
char *extarct_expand(char *cmd)
{
	int i;
	int index;
	char *to_expand;
	i = 0;
	while(cmd[i] && cmd[i] != '.' && cmd[i] != 32 && cmd[i] != '\'' && cmd[i] != '"')
		i++;
	to_expand = malloc (i + 1);
	if(!to_expand)
		return (NULL);
	index = 0;
	while(cmd[index] && cmd[index] != '.' && cmd[index] != 32 && cmd[index] != '\'' && cmd[index] != '"')
	{
		to_expand[index] = cmd[index];
		index++;
	}
	to_expand[index] = '\0';
	return (to_expand);
}
//extract after command
char *extarct_after(char *cmd)
{
	char *after;
	int index;
	int i;
	
	index = 0;
	i = 0;
	while(cmd[i])
		i++;
	after = malloc (i + 1);
	if(!after)
		return(NULL);
	while(cmd[index])
	{
		after[index] = cmd[index];
		index++;
	}
	after[index] = '\0';
	return (after);
}

void	ft_expand_vars(t_lexer **list, t_env *envp)
{
	char *before;
	char *after;
	char *to_expand;
	t_lexer	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			before = extract_before(tmp->str);
			while (*(tmp->str) != '$')
				tmp->str = tmp->str + 1;
			to_expand = extarct_expand(tmp->str);
			while(*(tmp->str) && *(tmp->str) != '.' && *(tmp->str) != 32 && *(tmp->str) != '\'' && *(tmp->str) != '"' )
				tmp->str = tmp->str + 1;
			after = extarct_after(tmp->str);
			to_expand = expand(to_expand + 1, envp);
			to_expand = ft_strjoin(before,to_expand);
			to_expand = ft_strjoin(to_expand,after);
			tmp->str = to_expand;
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
		new_node = create_token(tabs[index], ft_strlen(tabs[index]), NULL);
		new_node->type = ARGS;
		new_node->path = NULL;
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
	int index;

	index = 0;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == WILDCARD)
		{
			data = wildcard(tmp->str);
			if (!data || !*data)
				return ;
			tabs = ft_split(data, 32);
			if (!tabs)
				puts("split error");
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

void	clean_unsed_spaces(t_lexer	**list)
{
		t_lexer	*cur;
	t_lexer	*space;
	t_lexer	*tmp;
	
	tmp = *list;
	while(tmp)
	{
		if(tmp->type == CMD && tmp->prev && tmp->prev->type ==SPACE )
		{
			cur = tmp->prev->prev;
			space = tmp->prev;
			if(cur)
			{
				cur->next = tmp;
				tmp->prev = cur;
				free(space);
			}
			else
			{
				*list = tmp;
				tmp->prev = NULL;
				free(space);
			}
		}
		if(tmp->type == CMD && tmp->next && tmp->next->type == SPACE)
		{
			cur = tmp->next->next;
			space = tmp->next;
			tmp->next = cur;
			if(cur)
				cur->prev = tmp;
			free(space);
		}
		tmp = tmp->next;
	}
}

int	ft_expander(t_lexer *list, t_env *env)
{
	char **paths;

	paths = all_paths(env);
	ft_expand_vars(&list, env);
	if (check_qoutes(list) || check_pths(list))
		return (1);
	// join_args(&list, paths);
	// set_type(&list);
	if (syntax_analyzer(list))
		return (1);
	ft_expand_wildcards(&list);
	clean_unsed_spaces(&list);
	return (0);
}
