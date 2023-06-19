/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:31:26 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/19 14:29:16 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	check_path_exist(char *path, t_main *data)
{
	char	**paths;

	paths = all_paths(data->env);
	if (!paths)
		return (1);
	if (path_exist(path, paths))
		return (ft_free(paths), 0);
	return (ft_free(paths), 1);
}

char	*_path(t_tree *node, t_main *data)
{
	if (node->path && node->id != -1 && !node->is_builtin)
	{
		if (!check_path_exist(node->path, data))
			return (node->path);
		else
			return (NULL);
	}
	else if ((node->id == -1 && node->path) || !node->is_builtin)
	{
		if (node->type == VAR)
			return (expand(node->str, data->env, 1));
		else
			return (node->str);
	}
	return (NULL);
}

char	*mini_expander(t_lexer *node, t_main *data)
{
	char	*value;

	if (!ft_strncmp(node->str + 1, "?", 2))
		value = ft_itoa(exit_status);
	else
		value = expand(node->str, data->env, 1);
	if (value)
		return (value);
	else
		return (ft_strdup("\0"));
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
	ft_expand_vars(&node->cmd_args,data->env,tmp);
	// print_token_list(node->cmd_args);
	tmp = node->cmd_args;
	size = _args_size(tmp, node->is_builtin);
	cmd_args = malloc(sizeof(char *) * (size + 2));
	path = _path(node, data);
	if (path)
		cmd_args[index++] = ft_strdup(path);
	tmp = node->cmd_args;
	while (tmp)
	{
		// printf("%s\n",tmp->str);
		if (tmp->str && !ft_strncmp(tmp->str + 1, "?", 2))
			cmd_args[index++] = ft_itoa(exit_status);
		else if (tmp->str && tmp->type != W_SPACE)
			cmd_args[index++] = ft_strdup(tmp->str);
		// else if (!node->str)
		// 	cmd_args[index++] = ft_strdup("");
		// if (tmp->type == VAR)
		// 	cmd_args[index++] 
		// 	= ft_strdup(mini_expander(tmp, data));
		// else if (tmp->type != W_SPACE)
		// 		cmd_args[index++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
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
