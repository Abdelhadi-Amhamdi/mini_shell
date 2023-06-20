/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:31:26 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/20 16:20:55 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	check_path_exist(char *path, char **paths)
{
	if (!paths)
		return (1);
	if (path_exist(path, paths))
		return (0);
	return (1);
}

char	*_path(t_tree *node, t_main *data)
{
	char	**paths;

	paths = all_paths(data->env);
	if (!node->path && !node->is_builtin && node->type != W_SPACE && *node->str)
	{
		node->path = get_path(node->str, paths);
		ft_free(paths);
		if (!node->path)
			return (node->str);
		else
			return (node->path);
	}
	else if (node->path && !node->is_builtin)
	{
		if (!check_path_exist(node->path, paths))
			return (ft_free(paths), node->path);
		else
			return (ft_free(paths), node->str);
	}
	else if (node->type == W_SPACE || !(*node->str))
		return (ft_free(paths), node->str);
	return (ft_free(paths), NULL);
}

char	*exit_status_expand(t_lexer *node)
{
	char	*value;

	value = NULL;
	if (!ft_strncmp(node->str + 1, "?", 2))
		value = ft_itoa(g_exit_status);
	if (value)
		return (value);
	else
		return (ft_strdup("\0"));
}

void	copy_args_(t_lexer *list, char **tabs, int *i)
{
	t_lexer	*tmp;
	int		index;

	index = *i;
	tmp = list;
	while (tmp)
	{
		if (tmp->str && !ft_strncmp(tmp->str, "$?", 3))
			tabs[index++] = ft_itoa(g_exit_status);
		else if (tmp->str && tmp->str[0] == '$' && ft_isdigit(tmp->str[1]))
			tabs[index++] = ft_strdup(tmp->str + 2);
		else if (tmp->str && tmp->type != W_SPACE)
			tabs[index++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	*i = index;
}

char	**cmd_args_list_to_tabs(t_tree *node, t_main *data)
{
	char	**cmd_args;
	t_lexer	*tmp;
	int		size;
	int		index;
	char	*path;

	index = 0;
	tmp = node->cmd_args;
	ft_expand_vars(&node->cmd_args, data->env, tmp);
	tmp = node->cmd_args;
	size = _args_size(tmp, node->is_builtin);
	cmd_args = malloc(sizeof(char *) * (size + 2));
	if (!cmd_args)
		return (NULL);
	path = _path(node, data);
	if (path)
		cmd_args[index++] = ft_strdup(path);
	tmp = node->cmd_args;
	copy_args_(node->cmd_args, cmd_args, &index);
	cmd_args[index] = NULL;
	return (cmd_args);
}

char	**env_list_to_tabs(t_env *list)
{
	t_env	*tmp;
	char	**env;
	int		size;
	int		index;

	tmp = list;
	index = 0;
	size = env_list_size(tmp);
	env = malloc(sizeof(char *) * size + 1);
	if (!env)
		return (NULL);
	while (tmp)
	{
		env[index] = ft_strjoin(tmp->key, "=");
		env[index] = ft_strjoin(env[index], tmp->value);
		index++;
		tmp = tmp->next;
	}
	env[index] = NULL;
	return (env);
}
