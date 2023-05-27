/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:21:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/27 18:07:48 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

char *extract_str(char *str, int len)
{
	int i;
	char *s;

	s = malloc(len  + 1);
	if(!s)
		return (NULL);
	i = 0;
	while(i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

t_lexer	*create_token(char *str, int len, char **paths)
{
	t_lexer	*new;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = extract_str(str, len);
	new->is_oper = is_operator(new->str[0]);
	new->path = get_path(new->str, paths);
	new->is_builtin = is_builtin(new->str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

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
	while (tabs[index])
	{
		free(tabs[index]);
		index++;
	}
	free(tabs);
}

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

int is_absolute(char *str)
{
	while(*str)
	{
		if(*str == '/')
			return (1);
		str++;
	}
	return (0);
}

char *extract_cmd(char *cmd)
{
	char *new;
	int len;

	while(*cmd)
		cmd++;
	cmd--;
	len = 0;
	while (*cmd && *cmd != '/')
	{
		cmd--;
		len++;
	}
	cmd++;
	new = malloc ((len * sizeof(char )) + 1);
	if(!new)
		ft_error("Error in malloc");
	len = 0;
	while(*cmd)
	{
		new[len] = *cmd;
		cmd++;
		len++;
	}
	cmd[len] = '\0';
	return(new);
}

int validate_cmd(char *cmd)
{
	if(!access(cmd,F_OK | X_OK))
		return(0);
	return(1);
}

char *ft_word(t_lexer **list, char *cmd, char **paths)
{
	int i;
	t_lexer *new;
	i = 0;
	while(cmd[i] && !is_operator(cmd[i]) && cmd[i] != 32)
		i++;
	new = create_token(cmd, i, paths);
	add_token_to_end (list, new);
	return (&cmd[i]);
}

char *ft_spaces(t_lexer	**list, char *cmd, char **paths)
{
	t_lexer	*new;
	int i;

	i = 0;
	while(cmd[i] && is_space(cmd[i]))
		i++;
	new = create_token(cmd, i, paths);
	add_token_to_end (list, new);
	return (&cmd[i]);
}


char *ft_oneoperator(t_lexer **list, char *cmd, char c, char **paths)
{
	int i;
	t_lexer	*new;

	if(*(cmd+1) == c)
		i = 2;
	else
		i = 1;
	new = create_token(cmd, i, paths);
	add_token_to_end (list, new);
	return (&cmd[i]);
}

char *ft_parentheses(t_lexer	**list, char *cmd, char **paths)
{
	t_lexer	*new;
	int i;

	i = 1;
	new = create_token(cmd, i, paths);
	add_token_to_end (list, new);
	return (&cmd[i]);
}

char *ft_quotes(t_lexer	**list, char *cmd, char c, char **paths)
{
	t_lexer *new;
	int i;

	i = 1;
	while(cmd[i] && cmd[i] != c)
		i++;
	i++;
	new = create_token(cmd, i, paths);
	add_token_to_end (list, new);
	return (&cmd[i]);
}


t_lexer *tokenizer(char *cmd, char **paths)
{
	t_lexer	*list;

	list	= NULL;
	while(*cmd && is_space(*cmd))
		cmd++;
	while(*cmd)
	{
		if(is_space(*cmd))
			cmd = ft_spaces(&list,cmd,paths);
		else if (*cmd == '|')
			cmd = ft_oneoperator(&list,cmd, *cmd, paths);
		else if (*cmd == '&')
			cmd = ft_oneoperator(&list,cmd, *cmd, paths);
		else if (*cmd == '(' || *cmd == ')')
			cmd = ft_parentheses(&list, cmd,paths);
		else if (*cmd == '\'' || *cmd == '"')
			cmd = ft_quotes(&list, cmd, *cmd,paths);
		else if (*cmd == '>' || *cmd == '<')
			cmd = ft_oneoperator(&list, cmd, *cmd, paths);
		else
			cmd = ft_word(&list,cmd, paths);
	}
	return (list);
}

void set_type(t_lexer **list)
{
	t_lexer *tmp;

	tmp = *list;
	while (tmp)
	{
		tmp->type = check_type(tmp, tmp->path);
		tmp = tmp->next;
	}
}


t_lexer	*lexer(char *cmd, t_env	*env)
{
	char	**paths;
	t_lexer	*list;

	paths = all_paths(env);
	list = tokenizer(cmd, paths);
	set_type(&list);
	
	
	// while(list)
	// {
	// 	printf(":%s:\n",list->str);
	// 	list = list->next;
	// }
	// int		index;
	// char	**tabs;


	
	// index = 0;
	// list = NULL;
	// tabs = args_filter(args);
	// if (!tabs)
	// 	return (NULL);
	// while (tabs[index])
	// {
		
	// 	node = create_token(tabs[index], is_operator(tabs[index][0]), paths);
	// 	if (!node)
	// 		return (NULL);
	// 	if (!node->is_oper && !node->path)
	// 		node->path = get_path(node->str ,paths);
	// 	add_token_to_end(&list, node);
	// 	node = get_last_token(list);
		// node->type = check_type(node, node->path);
	// 	if((is_absolute(node->str) && !node->prev) || (is_absolute(node->str) && node->prev->type == PIPE))
	// 	{
	// 			if(validate_cmd(node->str))
	// 				return (ft_putendl_fd("command not found",2), NULL);
	// 			node->path = node->str;
	// 			node->str = extract_cmd(node->str);
	// 			node->type = CMD;
	// 	}
	// 	index++;
	// }
	// // print_token_list(list);
	// ft_free(tabs);
	// ft_free(paths);
	return (list);
}
