/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/16 17:52:54 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

// char	**get_path(t_env *env)
// {
// 	char	*path;

// 	path = NULL;
// 	while (env)
// 	{
// 		if (!ft_strncmp(env->key, "PATH", 4))
// 			path = env->value;
// 		env = env->next;
// 	}
// 	if (path)
// 		return (ft_split(path, ':'));
// 	return (NULL);
// }

// char	*filter_cmd(char *cmd, char **paths)
// {
// 	char	*command;
// 	char	*full_path;
// 	int		index;

// 	command = ft_strjoin("/", cmd);
// 	index = 0;
// 	if (!command)
// 		return (NULL);
// 	while (paths[index])
// 	{
// 		full_path = ft_strjoin(paths[index], command);
// 		if (!full_path)
// 			return (free (command), NULL);
// 		if (!access(full_path, F_OK | X_OK))
// 			return (free (command), full_path);
// 		free(full_path);
// 		index++;
// 	}
// 	free (command);
// 	return (NULL);
// }

// t_parser	*create_parser_node(t_lexer *l_node, char *path, int is_b)
// {
// 	t_parser	*new_node;

// 	new_node = malloc(sizeof(t_parser));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->is_builtin = is_b;
// 	new_node->path = path;
// 	new_node->str = l_node->str;
// 	new_node->type = check_type(l_node, path);
// 	new_node->next = NULL;
// 	new_node->prev = NULL;
// 	return (new_node);
// }

// void	add_node_to_list(t_parser **list, t_parser *item)
// {
// 	t_parser	*tmp;

// 	tmp = *list;
// 	if (!*list)
// 		*list = item;
// 	else
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = item;
// 		item->prev = tmp;
// 	}
// }

// t_parser	*parser(t_lexer *lexer_list, t_env *envp)
// {
// 	char		**paths;
// 	char		*path;
// 	t_parser	*new_node;
// 	t_parser	*parser_list;
// 	t_boolean	is_built;

// 	paths = get_path(envp);
// 	parser_list = NULL;
// 	new_node = NULL;
// 	while (lexer_list)
// 	{
// 		is_built = false;
// 		path = NULL;
// 		if (!lexer_list->is_token && (!new_node || new_node->type != 0))
// 			path = filter_cmd(lexer_list->str, paths);
// 		if (path || !lexer_list->is_token)
// 			is_built = is_builtin(lexer_list->str);
// 		new_node = create_parser_node(lexer_list, path, is_built);
// 		if (!new_node)
// 			return (NULL);
// 		add_node_to_list(&parser_list, new_node);
// 		lexer_list = lexer_list->next;
// 	}
// 	ft_free(paths);
// 	return (parser_list);
// }



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

// t_parser  *parser(t_lexer *lexer_list)
// {
// 	if (check_qoutes(lexer_list))
// 		return (NULL);

// }
