/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:23:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/20 20:30:55 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	is_exist(t_env *node, t_env *env)
{
	while (env)
	{
		if ((!ft_strncmp(node->key, env->key, ft_strlen(node->key))))
			return (1);
		env = env->next;
	}
	return (0);
}

t_env	*search_node(t_env *node, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, node->key, ft_strlen(node->key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (key && (!ft_isalpha(key[i]) && key[i] != '_' && key[i] != '\\'))
		return (1);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '\\')
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(t_tree *cmd, t_env **env, int out)
{
	t_env	*node;
	t_env	*list;
	t_env	*tmp;
	t_env	*cur;
	char	*key;
	char	*value;
	int		index;
	int valid;

	index = 0;
	if (!cmd->args[index])
		return (print_export(*env, out), 0);
	list=NULL;
	valid = 1;
	while (cmd->args[index])
	{
		formate_env_item(&key, &value, cmd->args[index]);
		if (check_key(key))
		{
			printf("mini-sh: export: `%s' not a valid identifier\n",cmd->args[index]);
			valid = 0;
		}
		node = ft_new_node(key, value);
		ft_add_back_env(&list, node);
		index++;
	}
	node = list;
	if (valid)
	{
		while (node)
		{
			tmp = node->next;
			if (node && !is_exist(node, *env))
				ft_add_back_env(env, node);
			else if (node && is_exist(node, *env) && node->value)
			{
				cur = search_node(node, *env);
				cur->value = node->value;
			}
			node = tmp;
		}
	}
	else
		return (1);
	return (0);
}
