/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:31:26 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/13 09:54:08 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int lexer_list_size(t_lexer *list, int is_b)
{
	int  size;

	size = 0;
	while (list && is_b)
	{
		list = list->next;
		size++;
	}
	while (list && !is_b)
	{
		if(list->type != W_SPACE)
			size++;
		list = list->next;
	}
	return (size);
}

void	print_tab(char** tab)
{
	int i;

	i = 0;
	while(tab[i])
		printf("[%s]\n",tab[i++]);
}

int path_exist(char *path, char **paths)
{
	int index;

	index = 0;
	while (paths[index])
	{
		if (!ft_strncmp(path, paths[index], ft_strlen(paths[index])))
			return (1);
		index++;
	}
	return (0);
}

int check_path_exist(char *path)
{
	char **paths;
	
	paths = all_paths(app->env_list);
	if (!paths)	
		return (1);
	if (path_exist(path, paths))
		return (ft_free(paths), 0);
	return (ft_free(paths), 1);
}

char **cmd_args_list_to_tabs(t_tree *node)
{
	char	**cmd_args;
	t_lexer	*tmp;
	int		size;
	int		index;
	char	*value;

	index = 0;
	if (node->type != CMD)	
		return (NULL);
	tmp = node->cmd_args;
	size = lexer_list_size(node->cmd_args, node->is_builtin);
	cmd_args = malloc(sizeof(char *) * (size + 2));
	if (node->path && node->id != -1 && !node->is_builtin)
	{
		if (!check_path_exist(node->path))
			cmd_args[index++] = ft_strdup(node->path);
		else 
			return (free(cmd_args), NULL);
	}
	else if ((node->id == -1 && node->path) || !node->is_builtin)
			cmd_args[index++] = ft_strdup(node->path);
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			if (!ft_strncmp(tmp->str, "$?", ft_strlen(tmp->str)))
				value = ft_itoa(app->status);
			else
				value = expand(tmp->str, app->env_list, 1);
			if (value)
			{
				cmd_args[index] = ft_strdup(value);
				index++;
			}
			
		}
		else
		{
			if(node->is_builtin)
			{
				cmd_args[index] = ft_strdup(tmp->str);
				index++;
			}
			else
			{
				if(tmp->type != W_SPACE)
				{
					cmd_args[index] = ft_strdup(tmp->str);
					index++;
				}
			}
		}
		tmp = tmp->next;	
	}
	cmd_args[index] = NULL;
	return (cmd_args);
}

int env_list_size(t_env *list)
{
	int index;
	
	index = 0;
	while (list)
	{
		index++;
		list = list->next;
	}
	return (index);
}

char **env_list_to_tabs(t_env *list)
{
	t_env *tmp;
	char **env;
	int size;
	int index;

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