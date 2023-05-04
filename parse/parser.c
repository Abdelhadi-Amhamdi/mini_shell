/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/04 13:59:02 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**get_path(char **tabs)
{
	int		index;
	char	*path;

	index = 0;
	path = NULL;
	while (tabs[index])
	{
		if (!ft_strncmp(tabs[index], "PATH=", 5))
			path = tabs[index];
		index++;
	}
	if (path)
		return (ft_split(path, ':'));
	return (NULL);
}

char	*filter_cmd(char *cmd, char **paths)
{
	char	*command;
	char	*full_path;
	int		index;

	command = ft_strjoin("/", cmd);
	index = 0;
	if (!command)
		return (NULL);
	while (paths[index])
	{
		full_path = ft_strjoin(paths[index], command);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK))
			return (full_path);
		index++;
	}
	return (NULL);
}

int	is_builtin(char *cmd)
{	
	if (ft_strncmp(cmd, "cd", 2) || ft_strncmp(cmd, "pwd", 3 \
	|| ft_strncmp(cmd, "echo", 4) || ft_strncmp(cmd, "export",\
	6)|| ft_strncmp(cmd, "unset", 5 || ft_strncmp(cmd, "exit", 4)))
		return (1);
	return (0);
}

t_type check_type(t_lexer *lexer_item, char *p)
{
	if (p)
		return (CMD);
	else if (lexer_item->is_token)
		return (TOKEN);
	else if(lexer_item->str[0] == '-')
		return (ARGS);
	return (UNK);
}

t_parser	*create_parser_node(t_lexer *l_node, char *path, t_boolean is_b)
{
	t_parser	*new_node;

	new_node = malloc(sizeof(t_parser));
	if (!new_node)
		return (NULL);
	new_node->is_builtin = is_b;
	new_node->path = path;
	new_node->str = l_node->str;
	new_node->type = check_type(l_node, path);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_node_to_list(t_parser **list, t_parser *item)
{
	if (!*list)
		*list = item;
	else
	{
		while((*list)->next)
			(*list) = (*list)->next;
		(*list)->next = item;
		item->prev = (*list);
	}
}

int	parser(t_lexer *lexer_list, char **envp)
{
	char		**paths;
	char		*path;
	t_parser	new_node;
	t_parser	parser_list;
	t_boolean	is_built;

	paths = get_path(envp);
	is_built = false;
	path = NULL;
	parser_list = NULL;
	while (lexer_list)
	{
		if(lexer_list->is_token)
		{
			path = filter_cmd(lexer_list->str, paths);
			if (path)
				is_built = is_builtin(lexer_list->str);	
		}
		new_node = create_parser_node(lexer_list, path, is_built);
		if (!new_node)
			return (NULL);
		add_node_to_list(&parser_list, new_node);
		lexer_list = lexer_list->next;
	}
	return (parser_list);
}