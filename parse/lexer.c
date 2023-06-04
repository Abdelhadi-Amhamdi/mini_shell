/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:21:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/04 12:40:06 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
//check is space
int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
//extract str from line command
char	*extract_str(char *str, int len)
{
	int		i;
	char	*s;

	s = malloc(len + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
//create new token
t_lexer	*create_token(char *str, int len, char **paths)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = extract_str(str, len);
	new->is_oper = is_operator(new->str[0]);
	if (paths)
		new->path = get_path(new->str, paths);
	new->is_builtin = is_builtin(new->str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
//add token to end of list
void	add_token_to_end(t_lexer **head, t_lexer *new_token)
{
	t_lexer	*current_token;

	current_token = *head;
	if (!current_token)
		*head = new_token;
	else
	{
		while (current_token->next != NULL)
			current_token = current_token->next;
		current_token->next = new_token;
		new_token->prev = current_token;
	}
}

void	ft_free(char **tabs)
{
	int	index;

	index = 0;
	if (!tabs || !*tabs)
		return ;
	while (tabs[index])
	{
		free(tabs[index]);
		index++;
	}
	free(tabs);
	tabs = NULL;
}
//get all paths
char	**all_paths(t_env *env)
{
	char	*path;

	path = NULL;
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 4))
			path = env->value;
		env = env->next;
	}
	if (path)
		return (ft_split(path, ':'));
	return (NULL);
}

int	isabs(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}
//extract command from abs path
char	*extract_cmd(char *cmd)
{
	char	*new;
	int		len;

	while (*cmd)
		cmd++;
	cmd--;
	len = 0;
	while (*cmd && *cmd != '/')
	{
		cmd--;
		len++;
	}
	cmd++;
	new = malloc((len * sizeof(char)) + 1);
	if (!new)
		ft_error("Error in malloc");
	len = 0;
	while (*cmd)
	{
		new[len] = *cmd;
		cmd++;
		len++;
	}
	cmd[len] = '\0';
	return (new);
}
//check is the path exits and valid
int	validate_cmd(char *cmd)
{
	if (!access(cmd, F_OK | X_OK))
		return (0);
	return (1);
}
//handle normal case
char	*ft_word(t_lexer **list, char *cmd, char **paths)
{
	int		i;
	t_lexer	*new;

	i = 0;
	while(cmd[i] && !is_operator(cmd[i]) && cmd[i] != 32 && cmd[i] != '\'' && cmd[i] != '"' && cmd[i] != '$' && cmd[i] != '(' && cmd[i] != ')')
		i++;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}
//handle spaces case
char	*ft_spaces(t_lexer **list, char *cmd, char **paths)
{
	t_lexer	*new;
	int		i;

	i = 0;
	while (cmd[i] && is_space(cmd[i]))
		i++;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}
//handle oneoperator case
char	*ft_oneoperator(t_lexer **list, char *cmd, char c, char **paths)
{
	int		i;
	t_lexer	*new;

	if (*(cmd + 1) == c)
		i = 2;
	else
		i = 1;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}
//handle parenthesses case
char	*ft_parentheses(t_lexer **list, char *cmd, char **paths)
{
	t_lexer	*new;
	int		i;

	i = 1;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}

char	*ft_quotes(t_lexer **list, char *cmd, char c, char **paths)
{
	t_lexer	*new;
	int		i;

	i = 1;
	while (cmd[i] && cmd[i] != c)
		i++;
	i++;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}

//handle variable case
char *ft_variable(t_lexer **list,char *cmd ,char **paths)
{
	t_lexer *new;
	int i;

	i = 1;
	while(cmd[i] && !is_space(cmd[i]) && cmd[i] != '$' && cmd[i] != '.' && cmd[i] != '\'' && cmd[i] != '"')
		i++;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}
//split cmd into tokens
t_lexer	*tokenizer(char *cmd, char **paths)
{
	t_lexer	*list;

	list = NULL;
	while (*cmd && is_space(*cmd))
		cmd++;
	while (*cmd)
	{
		if (is_space(*cmd))
			cmd = ft_spaces(&list, cmd, paths);
		else if (*cmd == '|')
			cmd = ft_oneoperator(&list, cmd, *cmd, paths);
		else if (*cmd == '&')
			cmd = ft_oneoperator(&list, cmd, *cmd, paths);
		else if (*cmd == '(' || *cmd == ')')
			cmd = ft_parentheses(&list, cmd, paths);
		else if (*cmd == '\'' || *cmd == '"')
			cmd = ft_quotes(&list, cmd, *cmd, paths);
		else if (*cmd == '>' || *cmd == '<')
			cmd = ft_oneoperator(&list, cmd, *cmd, paths);
		else if (*cmd == '$')
			cmd = ft_variable(&list, cmd, paths);
		else
			cmd = ft_word(&list, cmd, paths);
	}
	return (list);
}

void clean_white_spaces(t_lexer **list)
{
	t_lexer *tmp;
	t_lexer *prev_node;

	tmp = *list;
	while (tmp)
	{
		prev_node = NULL;
		tmp->type = check_type(tmp, tmp->path);
		if (tmp->type == SPACE && ((tmp->prev && tmp->prev->is_oper) || (tmp->next && tmp->next->is_oper)))
		{
			prev_node = tmp->prev;
			prev_node->next = tmp->next;
		}
		tmp = tmp->next;
	}
}

// loop over the list and set types
void set_type(t_lexer **list)
{
	t_lexer	*tmp;

	tmp = *list;
	while (tmp)
	{
		tmp->type = check_type(tmp, tmp->path);
		// if ((isabs(tmp->str) && !tmp->prev) || (isabs(tmp->str)
		// 		&& tmp->prev->type == PIPE) || (isabs(tmp->str)
		// 		&& tmp->prev->prev->type == PIPE) || (isabs(tmp->str)
		// 		&& tmp->prev->type == AND) || (isabs(tmp->str)
		// 		&& tmp->prev->prev->type == AND) || (isabs(tmp->str)
		// 		&& tmp->prev->type == OR) || (isabs(tmp->str)
		// 		&& tmp->prev->prev->type == OR))
		// {
		// 	if (validate_cmd(tmp->str))
		// 		return (ft_putendl_fd("command not found", 2));
		// 	tmp->path = tmp->str;
		// 	tmp->str = extract_cmd(tmp->str);
		// 	tmp->type = CMD;
		// }
		tmp = tmp->next;
	}
}

void del_node(t_lexer *node)
{
	if (!node)
		return ;
	free(node->str);
	node->str = NULL;
	if (node->path)
		free(node->path);
	node->path = NULL;
	free(node);
	node = NULL;
}

void	clean_spaces(t_lexer	**list)
{
	t_lexer	*cur;
	t_lexer	*space;
	t_lexer	*tmp;
	
	tmp = *list;
	while(tmp)
	{
		if(tmp->is_oper && tmp->prev && tmp->prev->type == SPACE )
		{
			cur = tmp->prev->prev;
			space = tmp->prev;
			if(cur)
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
		if(tmp->is_oper && tmp->next && tmp->next->type == SPACE)
		{
			cur = tmp->next->next;
			space = tmp->next;
			tmp->next = cur;
			if(cur)
				cur->prev = tmp;
			del_node(space);
		}
		tmp = tmp->next;
	}
}

// get rid of quotes and check if the arg are empty
void	ft_trim_quotes(t_lexer *node)
{
	t_lexer	*tmp;
	char	*str_tmp;

	tmp = node;
	if (!tmp)
		return ;
	str_tmp = tmp->str;
	if (tmp->type == SQ)
		tmp->str = ft_strtrim(tmp->str, "'");
	else if (tmp->type == DQ)
		tmp->str = ft_strtrim(tmp->str, "\"");
	if (!tmp->str[0])
	{
		tmp->str = " ";
		tmp->type = SPACE;
	}
	else
		tmp->type = UNK;
	free(str_tmp);
}

// check if the quotes are closed and get rid of them
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
				return (ft_putendl_fd("Syntax Error \"'", 2), 1);
			ft_trim_quotes(tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}

// check if the node need to be joined with the next node
int to_join(t_lexer *node)
{
	if (node && !node->is_oper && node->type != SPACE && \
	node->type != OP && node->type != CP && node->type != VAR)
		return (1);
	return (0);
}

// join args that no space or operator between them
void join_args(t_lexer **list, char **paths)
{
	t_lexer *tmp;
	t_lexer *next_tmp;
	char	*str_tmp;

	tmp = *list;
	while (tmp)
	{
		if (to_join(tmp) && to_join(tmp->next))
		{
			str_tmp = tmp->str;
			next_tmp = tmp->next;
			tmp->str = ft_strjoin(tmp->str, tmp->next->str);
			free(str_tmp);
			tmp->path = get_path(tmp->str, paths);
			tmp->next = tmp->next->next;
			del_node(next_tmp);
		}
		tmp = tmp->next;
	}
}

int check_pths(t_lexer *list)
{
	int op;
	int cp;

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
		return (ft_putendl_fd("Syntax Error )(", 2), 1);
	return (0);
}

// main lexer function
t_lexer	*lexer(char *cmd, t_env *env)
{
	char	**paths;
	t_lexer	*list;

	paths = all_paths(env);
	list = tokenizer(cmd, paths);
	set_type(&list);
	clean_spaces(&list);
	// 	if((is_absolute(node->str) && !node->prev) || (is_absolute(node->str)
					// && node->prev->type == PIPE))
	// 	{
	// 			if(validate_cmd(node->str))
	// 				return (ft_putendl_fd("command not found",2), NULL);
	// 			node->path = node->str;
	// 			node->str = extract_cmd(node->str);
	// 			node->type = CMD;
	// 	}
	// 	index++;
	// }
	// set_type(&list);
	ft_free(paths);
	// print_token_list(list);
	return (list);
}
