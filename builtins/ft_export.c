/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:23:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/22 10:12:09 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_env	*search_node(t_env *node, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, node->key, ft_strlen(node->key) + 1))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_key(char *key)
{
	int	i;
	int	len;

	i = 0;
	if (!key || !*key)
		return (1);
	len = ft_strlen(key) - 1;
	if (((!ft_isalpha(key[i]) && key[i] != '_' && key[i] != '\\')
			|| (key[len] != '+' && !ft_isalnum(key[len]) && key[i] != '_'
				&& key[len] != '\\')))
		return (1);
	i++;
	while (key[i] && key[i + 1])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '\\')
			return (1);
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
		free(tmp);
	}
}

void	add_new_env_node(char *key, char *value, t_env **env)
{
	t_env	*node;
	char	*tmp;
	t_env	*cur;

	node = ft_new_node(key, value);
	if (node->key[ft_strlen(node->key) - 1] == '+')
		_appand_var(node, *env);
	if (node && !is_exist(node, *env))
	{
		ft_add_back_env(env, node);
	}
	else if (node && is_exist(node, *env) && node->value)
	{
		cur = search_node(node, *env);
		if (cur)
		{
			tmp = cur->value;
			cur->value = ft_strdup(node->value);
			free(tmp);
		}
		del_env_node(node);
	}
	else
		del_env_node(node);
}

int	ft_export(t_tree *cmd, t_env **env, int out)
{
	char	*key;
	char	*value;
	int		index;
	int		exit_s;

	index = 0;
	if (!cmd->args[index])
		return (print_export(*env, out), 0);
	exit_s = 0;
	while (cmd->args[index])
	{
		formate_env_item(&key, &value, cmd->args[index]);
		if (!key || check_key(key))
		{
			print_err(cmd->args[index], &exit_s);
			free(key);
			free(value);
		}
		else
			add_new_env_node(key, value, env);
		index++;
	}
	return (exit_s);
}
