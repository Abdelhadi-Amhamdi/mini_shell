/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:31:26 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/25 22:12:05 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*_path(t_tree *node, t_main *data)
{
	char	**paths;

	paths = all_paths(data->env);
	if (!node->str)
		return (none_str(node, data, paths));
	if (!node->path && !node->is_builtin && node->type != W_SPACE && *node->str)
	{
		node->path = get_path(node->str, paths);
		ft_free(paths);
		if (!node->path)
			return (ft_strdup(node->str));
		else
			return (node->path);
	}
	if (node->path && !node->is_builtin)
	{
		if (!check_path_exist(node->path, paths))
			return (ft_free(paths), ft_strdup(node->path));
		else
			return (ft_free(paths), ft_strdup(node->str));
	}
	else if (node->type == W_SPACE || !(*node->str))
		return (ft_free(paths), ft_strdup(node->str));
	return (ft_free(paths), NULL);
}

void	copy_args_(t_lexer *list, char **tabs, int *i)
{
	t_lexer	*tmp;
	int		index;

	index = *i;
	tmp = list;
	while (tmp)
	{
		if (tmp->str && tmp->str[0] == '$' && ft_isdigit(tmp->str[1]))
			tabs[index++] = ft_strdup(tmp->str + 2);
		else if (tmp->str && (tmp->type != W_SPACE || tmp->id == -14))
			tabs[index++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	*i = index;
}

char	**_args_tabs(t_tree *node, t_main *data)
{
	char	**cmd_args;
	t_lexer	*tmp;
	int		size;
	int		index;
	char	*path;

	index = 0;
	if (!node)
		return (NULL);
	tmp = node->cmd_args;
	ft_expand_vars(&node->cmd_args, data->env, tmp);
	tmp = node->cmd_args;
	size = _args_size(tmp);
	cmd_args = malloc(sizeof(char *) * (size + 1 + !node->is_builtin));
	if (!cmd_args)
		return (NULL);
	path = _path(node, data);
	if (path)
		cmd_args[index++] = path;
	copy_args_(node->cmd_args, cmd_args, &index);
	cmd_args[index] = NULL;
	return (cmd_args);
}

char	**env_tabs(t_env *list)
{
	t_env	*tmp;
	char	**env;
	int		size;
	int		index;

	tmp = list;
	index = 0;
	size = env_list_size(tmp);
	env = malloc(sizeof(char *) * (size + 1));
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

int	check_path_exist(char *path, char **paths)
{
	if (!paths)
		return (1);
	if (path_exist(path, paths))
		return (0);
	return (1);
}
