/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/13 16:26:38 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char *ft_get_expand_val(char *var, t_env	*envp)
{
	while (envp)
	{
		if (!ft_strncmp(var, envp->key, ft_strlen(envp->key) + 1))
			return (ft_strdup(envp->value));
		envp = envp->next;
	}
	return (NULL);
}

char *get_string(char *s, int *index, t_env	*envp, int last)
{
	int	begining= *index;
	char *old;
	char *var;
	int start;
	int len=0;
	int i;
	char *str;

	start = *index;
	i = 0;
	if(s[*index] == '$' || s[*index] == '/' || s[*index] == '.' || s[*index] == 32)
	{
		len++;
		*index = *index + 1;
	}
	while(s[*index] && s[*index] != 32 && s[*index] != '/' && s[*index] != '.' && s[*index] != '$')
	{
		len++;
		*index = *index + 1;
	}
	var = malloc (len + 1);
	if(!var)
		return(ft_putendl_fd("Malloc Failed\n",2),NULL);
	if(s[start] == '$' || s[start] == '/' || s[start] == '.' || s[start] == 32)
		var[i++] = s[start++];
	while(s[start] && s[start] != 32 && s[start] != '/' && s[start] != '.' && s[start] != '$')
		var[i++] =s[start++];
	var[i] = '\0';
	str = ft_get_expand_val(var + 1, envp);
	if(var[0] == '$' && str)
	{
		old = var;
		var = str;
		free(old);
	}
	else if (!str && last && s[begining] == '$')
		var = NULL;
	return(var);
}

char	*expand(char *var, t_env *envp, int last)
{
	int i;
	char *str;
	char *new;
	char *old;
	
	i = 0;
	str = get_string(var,&i, envp, last);
	while(var[i])
	{
		old = str;
		new = get_string(var, &i, envp, last);
		str = ft_strjoin(str,new);
		free(old);
		free(new);
	}
	return(str);
}
//extarct before command
char	*extract_before(char *cmd, int *i)
{
	int		start;
	int		len;
	int		index;
	char	*before;

	len = 0;
	start = *i;
	while (cmd[*i] && (cmd[*i] == '\'' || cmd[*i] == '"'))
	{
		*i = *i + 1;
		len++;
	}
	before = malloc(len + 1);
	if (!before)
		return (NULL);
	index = 0;
	while (cmd[start] && (cmd[start] == '\'' || cmd[start] == '"'))
	{
		before[index] = cmd[start];
		index++;
		start++;
	}
	before[index] = '\0';
	return (before);
}
//extract variable to expland
char	*extarct_expand(char *cmd, int *i)
{
	int		start;
	int		len;
	int		index;
	char	*to_expand;

	start = *i;
	len = 0;
	// && cmd[*i] != '.' && cmd[*i] != 32 && 
	while (cmd[*i] && cmd[*i] != '\'' && cmd[*i] != '"')
	{
		*i = *i + 1;
		len++;
	}
	to_expand = malloc(len + 1);
	if (!to_expand)
		return (NULL);
	index = 0;
	// && cmd[start] != '.' && cmd[start] != 32
	while (cmd[start] && cmd[start] != '\'' && cmd[start] != '"')
	{
		to_expand[index] = cmd[start];
		index++;
		start++;
	}
	to_expand[index] = '\0';
	return (to_expand);
}
//extract after command
char	*extarct_after(char *cmd, int *i)
{
	int		start;
	char	*after;
	int		index;
	int		len;

	index = 0;
	len = 0;
	start = *i;
	while (cmd[*i])
	{
		len++;
		*i = *i + 1;
	}
	after = malloc(len + 1);
	if (!after)
		return (NULL);
	while (cmd[start])
	{
		after[index] = cmd[start];
		index++;
		start++;
	}
	after[index] = '\0';
	return (after);
}
//remove nodes with null str
// void	remove_node(t_lexer	**list, t_lexer	*node)
// {
// 	t_lexer	*tmp;
// 	t_lexer	*prev;
// 	t_lexer	*next;

// 	tmp = *list;
// 	while(tmp)
// 	{
// 		if(tmp == node)
// 			break ;
// 		tmp = tmp->next;
// 	}
// 	prev = tmp->prev;
// 	next = tmp->next;
// 	if(prev && prev->type == SPACE)
// 		prev = prev->prev;
// 	if(next && next->type == SPACE)
// 		next = next->next;
// 	if(!prev)
// 	{
// 		*list = next;
// 		if(next)
// 			next->prev = *list;
// 		free(tmp);
// 	}
// 	else
// 	{
// 		prev->next = next;
// 		if(next)
// 			next->prev = prev;
// 		free(tmp);
// 	}
// }

void	remove_node(t_lexer **list, t_lexer *node)
{
	t_lexer	*tmp;
	t_lexer	*prev;
	t_lexer	*next;

	tmp = *list;
	while (tmp)
	{
		if (tmp == node)
			break ;
		tmp = tmp->next;
	}
	prev = tmp->prev;
	if (prev && prev->type == W_SPACE)
	{
		while (prev->type == W_SPACE && prev)
			prev = prev->prev;
	}
	next = tmp->next;
	if (!prev && !next)
	{
		*list = NULL;
		free(node);
		return ;
	}
	if (!prev)
	{
		*list = next;
		if (next)
			next->prev = *list;
		free(node);
	}
	else
	{
		prev->next = next;
		if (next)
			next->prev = prev;
		free(node);
	}
}
//expand variables
void	ft_expand_vars(t_lexer **list, t_env *envp)
{
	t_lexer	*tmp;
	char	*before;
	char	*after;
	char	*var;
	char	*temp;
	int		i;

	tmp = *list;
	while (tmp)
	{
		i = 0;
		if (tmp->type == VAR)
		{
			before = extract_before(tmp->str, &i);
			var = extarct_expand(tmp->str, &i);
			after = extarct_after(tmp->str, &i);
			temp = var;
			var = expand(var, envp, 0);
			if (!var)
			{
				free(temp);
				tmp = tmp->next;
			}
			else
			{
				free(temp);
				temp = var;
				var = ft_strjoin(before, var);
				free(temp);
				temp = var;
				var = ft_strjoin(var, after);
				free(temp);
				temp = tmp->str;
				tmp->str = var;
				free(temp);
				tmp = tmp->next;
			}
			free(before);
			free(after);
		}
		else
			tmp = tmp->next;
	}
}

int	check_opeators(t_lexer *op)
{
	if (!op->next || (op->next->type == CP || \
	(op->next->is_oper && op->next->type != RDIR && op->next->type != HEREDOC && op->next->type != APND)))
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
		else if (tmp->type == UNK && (!ft_strncmp(tmp->str, ";;",
						ft_strlen(tmp->str))))
			res += ft_error(tmp->str);
		if (res)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_lexer	*create_list(char **tabs)
{
	int		index;
	t_lexer	*list;
	t_lexer	*new_node;

	index = 0;
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

t_lexer	*get_last_token(t_lexer *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_expand_wildcards(t_lexer **list)
{
	t_lexer	*tmp;
	t_lexer	*last;
	t_lexer	*new_list;
	char	*data;
	char	**tabs;
	int		index;

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
			del_node(tmp);
			ft_free(tabs);
			free(data);
			data = NULL;
			tmp = last->next;
		}
		else
			tmp = tmp->next;
	}
}

void	clean_unsed_spaces(t_lexer **list)
{
	t_lexer	*cur;
	t_lexer	*space;
	t_lexer	*tmp;

	tmp = *list;
	while (tmp)
	{
		if ((tmp->type == CMD || tmp->type == OP || tmp->type == CP) && tmp->prev && tmp->prev->type == W_SPACE)
		{
			cur = tmp->prev->prev;
			space = tmp->prev;
			if (cur)
			{
				cur->next = tmp;
				tmp->prev = cur;
				del_node(space);
			}
			else
			{
				*list = tmp;
				tmp->prev = NULL;
				del_node(space);
			}
		}
		if ((tmp->type == CMD || tmp->type == OP || tmp->type == CP) && tmp->next && tmp->next->type == W_SPACE)
		{
			cur = tmp->next->next;
			space = tmp->next;
			tmp->next = cur;
			if (cur)
				cur->prev = tmp;
			del_node(space);
		}
		tmp = tmp->next;
	}
}

int	is_linked_var(t_lexer *node)
{
	int	i;

	i = 0;
	while (node->str[i])
	{
		if (node->str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	add_to_list(t_lexer **list, t_lexer *prev, t_lexer *new, t_lexer *next)
{
	t_lexer	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp == prev)
			break ;
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
	new->next = next;
	if (next)
		next->prev = new;
}
//please don't remove me
char	*get_newstr(char *str, int *index)
{
	char	*new;
	int		start;
	int		i;
	int		len;

	len = 0;
	start = *index;
	if (str[*index] == '$' || str[*index] == '\'' || str[*index] == '.')
	{
		*index = *index + 1;
		len++;
	}
	while (str[*index] && str[*index] != '$' && str[*index] != '\''
		&& str[*index] != '.' && str[*index] != 32)
	{
		len++;
		*index = *index + 1;
	}
	new = malloc(len + 1);
	i = 0;
	if (str[start] == '$' || str[start] == '\'' || str[start] == '.')
		new[i++] = str[start++];
	while (str[start] && str[start] != '$' && str[start] != '\''
		&& str[start] != '.' && str[start] != 32)
	{
		new[i] = str[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
//me too please
char	*get_spacestr(char *str, int *index)
{
	char	*new;
	int		start;
	int		i;
	int		len;

	len = 0;
	start = *index;
	while (str[*index] == 32 && str[*index])
	{
		*index = *index + 1;
		len++;
	}
	new = malloc(len + 1);
	i = 0;
	while (str[start] == 32 && str[start])
	{
		new[i] = str[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
//i don't some stuipd shit don't remove
void	add_new_node(t_lexer **list, t_lexer *node)
{
	char	*current;
	int		i;
	t_lexer	*next;
	t_lexer	*tmp;
	t_lexer	*new;

	tmp = *list;
	while (tmp)
	{
		if (tmp == node)
			break ;
		tmp = tmp->next;
	}
	i = 0;
	next = tmp->next;
	current = tmp->str;
	tmp->str = get_newstr(current, &i);
	while (current[i])
	{
		new = malloc(sizeof(t_lexer));
		if (current[i] == 32)
			new->str = get_spacestr(current, &i);
		else
			new->str = get_newstr(current, &i);
		new->is_builtin = is_builtin(new->str);
		new->is_oper = is_operator(new->str[0]);
		new->path = NULL;
		add_to_list(list, tmp, new, next);
		new->type = check_type(new, new->path);
		tmp = new;
	}
	free(current);
}
//also don't remove
void	check_variables(t_lexer **list)
{
	t_lexer	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			if (is_linked_var(tmp))
				add_new_node(list, tmp);
		}
		tmp = tmp->next;
	}
}

void	check_asbpath(t_lexer **list)
{
	t_lexer	*tmp;

	tmp = *list;
	while (tmp)
	{
		if ((isabs(tmp->str) && !tmp->prev) || (isabs(tmp->str)
				&& tmp->prev->type == PIPE) || (isabs(tmp->str)
				&& tmp->prev->type == AND) || (isabs(tmp->str)
				&& tmp->prev->type == OR) || (isabs(tmp->str)
				&& tmp->prev->type == OP))
		{
			tmp->path = tmp->str;
			tmp->str = extract_cmd(tmp->str);
			tmp->type = CMD;
			tmp->id = -1;
		}
		tmp = tmp->next;
	}
}

int	ft_expander(t_lexer *list, t_env *env)
{
	char	**paths;

	paths = all_paths(env);
	ft_expand_vars(&list, env);
	if (check_qoutes(list) || check_pths(list))
	{
		app->status = SYNTAX_ERROR_EXIT_STATUS;
		return (ft_free(paths), 1);
	}
	// check_variables(&list);
	check_asbpath(&list);
	join_args(&list, paths);
	set_type(&list);
	clean_unsed_spaces(&list);
	if (syntax_analyzer(list))
	{
		app->status = SYNTAX_ERROR_EXIT_STATUS;
		return (ft_free(paths), 1);
	}
	ft_expand_wildcards(&list);
	return (ft_free(paths), 0);
}
