/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:31:26 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/05 13:35:25 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int lexer_list_size(t_lexer *list)
{
	int  size;

	size = 0;
	while (list)
	{
		list = list->next;
		size++;
	}
	return (size);
}

char **cmd_args_list_to_tabs(t_tree *node)
{
	char	**cmd_args;
	t_lexer	*tmp;
	int		size;
	int		index;

	index = 0;
	if (node->type != CMD)	
		return (NULL);
	tmp = node->cmd_args;
	size = lexer_list_size(node->cmd_args);
	cmd_args = malloc(sizeof(char *) * (size + 2));
	cmd_args[index++] = ft_strdup(node->path);
	while (tmp)
	{
		cmd_args[index] = ft_strdup(tmp->str);
		tmp = tmp->next;
		index++;
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