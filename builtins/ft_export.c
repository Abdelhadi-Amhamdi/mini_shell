/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:23:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/11 17:56:42 by aagouzou         ###   ########.fr       */
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

void	print_export(t_env	*env)
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
	while(env->next)
	{
		printf("declare -x %s=\"%s\"\n",env->key, env->value);
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

void	ft_export(t_parser *full_cmd, t_env **env)
{
	t_env	*node;
	char *key;
	char *value;
	
	if(!full_cmd->next)
	{
		print_export(*env);
		return ;	
	}
	formate_env_item(&key, &value, full_cmd->next->str);
	node = ft_new_node(key, value);
	if (node)
			ft_add_back_env(env, node); 
}
