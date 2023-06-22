/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:23:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/21 20:33:59 by aagouzou         ###   ########.fr       */
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
	if (key && (!ft_isalpha(key[i]) && key[i] != '_' && key[i] \
	!= '\\' && key[ft_strlen(key) - 1] != '+'))
		return (1);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '\\')
		{
			if (key[ft_strlen(key) - 1] != '+')
				return (1);
		}
		i++;
	}
	return (0);
}

void	_appand_var(t_env *node, t_env *env)
{
	t_env	*tmp_node;
	char	*tmp;

	node->key[ft_strlen(node->key) - 1] = '\0';
	tmp_node = ft_search_env(env, node->key);
	if (tmp_node)
	{
		tmp = node->value;
		node->value = ft_strjoin(tmp_node->value, node->value);
		free (tmp);
	}
}

int	ft_export(t_tree *cmd, t_env **env, int out)
{
	t_env	*node;
	t_env	*cur;
	char	*key;
	char	*value;
	int		index;
	int exit_s;

	index = 0;
	if (!cmd->args[index])
		return (print_export(*env, out), 0);
	exit_s = 0;
	while (cmd->args[index])
	{
		formate_env_item(&key, &value, cmd->args[index]);
		if (!key || check_key(key))
		{
			printf("mini-sh: export: `%s' not a valid identifier\n", cmd->args[index]);
			exit_s = 1;
		}
		else
		{
			node = ft_new_node(key, value);
			if (key[ft_strlen(key) - 1] == '+')
				_appand_var(node, *env);
			else if (node && !is_exist(node, *env))
				ft_add_back_env(env, node);
			else if (node && is_exist(node, *env) && node->value)
			{
				cur = search_node(node, *env);
				cur->value = node->value;
			}
		}
		index++;
	}
	return (exit_s);
}
