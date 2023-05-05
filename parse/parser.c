/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/05 16:22:38 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	**get_path(t_env *env)
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
		if (!access(full_path, F_OK | X_OK))
			return (full_path);
		index++;
	}
	return (NULL);
}

t_parser	*create_parser_node(t_lexer *l_node, char *path, int is_b)
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
	t_parser	*tmp;

	tmp = *list;
	if (!*list)
		*list = item;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = item;
		item->prev = tmp;
	}
}

t_parser	*parser(t_lexer *lexer_list, t_env *envp)
{
	char		**paths;
	char		*path;
	t_parser	*new_node;
	t_parser	*parser_list;
	t_boolean	is_built;

	paths = get_path(envp);
	parser_list = NULL;
	new_node = NULL;
	while (lexer_list)
	{
		is_built = false;
		path = NULL;
		if (!lexer_list->is_token && (!new_node || new_node->type != 0))
			path = filter_cmd(lexer_list->str, paths);
		if (path)
			is_built = is_builtin(lexer_list->str);
		new_node = create_parser_node(lexer_list, path, is_built);
		if (!new_node)
			return (NULL);
		add_node_to_list(&parser_list, new_node);
		lexer_list = lexer_list->next;
	}
	return (parser_list);
}
