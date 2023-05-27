/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:21:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/27 15:57:34 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

t_lexer	*create_token(char *str, int len)
{
	t_lexer	*new;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = extract_str(str, len);
	new->path = NULL;
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

int is_space(char c)
{
	return (c == 32);
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

char *ft_word(t_lexer **list, char *cmd)
{
	int i;
	t_lexer *new;
	i = 0;
	while(cmd[i] && !is_operator(cmd[i]))
		i++;
	new = create_token(cmd, i);
	add_token_to_end (list, new);
	return (&cmd[i]);
}

char *ft_spaces(t_lexer	**list, char *cmd)
{
	t_lexer	*new;
	int i;

	i = 0;
	while(cmd[i] && is_space(cmd[i]))
		i++;
	new = create_token(cmd, i);
	add_token_to_end (list, new);
	return (&cmd[i]);
}

char *ft_and(t_lexer **list, char *cmd)
{
	int i;
	t_lexer	*new;

	if(*(cmd + 1) == '&')
		i = 2;
	else
		i = 1;
	new = create_token(cmd, i);
	add_token_to_end (list, new);
	return (&cmd[i]);
}

char *ft_pipe(t_lexer **list, char *cmd)
{
	int i;
	t_lexer	*new;

	if(*(cmd+1) == '|')
		i = 2;
	else
		i = 1;
	new = create_token(cmd, i);
	add_token_to_end (list, new);
	return (&cmd[i]);
}

char *ft_parentheses(t_lexer	**list, char *cmd)
{
	t_lexer	*new;
	int i;

	i = 1;
	new = create_token(cmd, i);
	add_token_to_end (list, new);
	return (&cmd[i]);
}

char *ft_singleq(t_lexer	**list, char *cmd)
{
	t_lexer *new;
	int i;

	i = 1;
	while(cmd[i] && cmd[i] != '\'')
		i++;
	i++;
	new = create_token(cmd, i);
	add_token_to_end (list, new);
	return (&cmd[i]);
}

char *ft_doubleq(t_lexer	**list, char *cmd)
{
	t_lexer *new;
	int i;

	i = 1;
	while(cmd[i] && cmd[i] != '"')
		i++;
	i++;
	new = create_token(cmd, i);
	add_token_to_end (list, new);
	return (&cmd[i]);
}

t_lexer	*lexer(char *cmd, t_env	*env)
{
	t_lexer	*list;

	(void)env;
	list	= NULL;
	while(*cmd)
	{
		if(is_space(*cmd))
			cmd = ft_spaces(&list,cmd);
		else if (*cmd == '|')
			cmd = ft_pipe(&list,cmd);
		else if (*cmd == '&')
			cmd = ft_and(&list,cmd);
		else if (*cmd == '(' || *cmd == ')')
			cmd = ft_parentheses(&list, cmd);
		else if (*cmd == '\'')
			cmd = ft_singleq(&list, cmd);
		else if (*cmd == '"')
			cmd = ft_doubleq(&list, cmd);
		else
			cmd = ft_word(&list,cmd);
	}
	
	while(list)
	{
		printf("=:%s:\n",list->str);
		list = list->next;
	}
	// char	**paths;
	// int		index;
	// char	**tabs;


	
	// index = 0;
	// list = NULL;
	// tabs = args_filter(args);
	// if (!tabs)
	// 	return (NULL);
	// paths = all_paths(env);
	// while (tabs[index])
	// {
		
	// 	node = create_token(tabs[index], is_operator(tabs[index][0]), paths);
	// 	if (!node)
	// 		return (NULL);
	// 	if (!node->is_oper && !node->path)
	// 		node->path = get_path(node->str ,paths);
	// 	add_token_to_end(&list, node);
	// 	node = get_last_token(list);
	// 	node->type = check_type(node, node->path);
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
