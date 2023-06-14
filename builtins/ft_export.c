/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:23:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/14 21:37:41 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"


t_env	*smallest_env_key(t_env *env, t_env *node)
{
	t_env	*smallest;

	smallest = env;
	while(env)
	{
		if(node->key[0] <= smallest->key[0] )
			smallest = node;
		env = env->next;
	}
	printf("smallest of %s is %s\n",smallest->key, node->key);
	return(smallest);
}

int	count_env(t_env *env)
{
	int i;

	i = 0;
	while(env)
	{
		i++;
		env= env->next;
	}
	return(i);
}

void	print_export(t_env	*env, int out)
{
	t_env *cur;
	t_env *tmp;
	char *key;
	char *value;

	cur = env;
	while(cur)
	{
		tmp = cur->next;
		while(tmp)
		{
			if(tmp->key[0] < cur->key[0])
			{
				key = tmp->key;
				value = tmp->value;
				tmp->key = cur->key;
				tmp->value = cur->value;
				cur->key = key;
				cur->value = value;
			}
			tmp = tmp->next;
		}
		cur = cur->next;
	}
	while(env)
	{
		if(env->key && env->value && ft_strncmp(env->key,"_", 2))
		{
			ft_putstr_fd("declare -x ", out);
			ft_putstr_fd(env->key, out);
			ft_putstr_fd("=\"", out);
			ft_putstr_fd(env->value, out);
			ft_putendl_fd("\"", out);
		}
		else if(env->key && !env->value)
		{
			ft_putstr_fd("declare -x ", out);
			ft_putendl_fd(env->key, out);
		}
		env = env->next;
	}

}
int check_spaces(char *str)
{
	int i;

	i = 0;
	if(str[i] == '=')
	{
		ft_putendl_fd("export :not a valid identifier", STDERR_FILENO);
		return (0);
	}
	while (str[i])
	{
		if(str[i] == '=' && str[i] == 32)
			return (0);
		i++;
	}
	return (1);	
}


int is_exist(t_env	*node, t_env	*env)
{
	while(env)
	{
		if((!ft_strncmp(node->key, env->key, ft_strlen(node->key))))
			return (1);
		env = env->next;
	}	
	return (0);
}

t_env	*search_node(t_env	*node, t_env	*env)
{
	t_env	*tmp;

	tmp = env;
	while(tmp)
	{
		if(!ft_strncmp(tmp->key, node->key, ft_strlen(node->key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

int check_key(char *key)
{
	int i;

	i = 0;
	if(key && (!ft_isalpha(key[i]) && key[i] != '_' && key[i] == '\\'))
		return(1);
	i++;
	while(key[i])
	{
		if(!ft_isalnum(key[i]) && key[i] != '_' && key[i] == '\\')
			return(1);
		i++;
	}
	return (0);
}

int	ft_export(t_tree *cmd, t_env **env, int out)
{
	t_env	*node;
	t_env	*tmp;
	char *key;
	char *value;
	int i;

	i = 0;
	if(!cmd->args[i])
	{
		print_export(*env, out);
		return (0);
	}
	while(cmd->args[i])
	{
		formate_env_item(&key, &value, cmd->args[i]);
		if(check_key(key))
			return(ft_putendl_fd("export: not a valid identifier",2), 1);
		node = ft_new_node(key, value);
		if (node && !is_exist(node, *env))
			ft_add_back_env(env, node);
		else if(node && is_exist(node, *env))
		{
			tmp = search_node(node, *env);
			tmp->value = value;
		}
		i++;
	}
	return (0);
}
