/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:23:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/09 14:44:45 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	print_export(t_env	*env)
{
	(void) env;
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

void	ft_export(char *new_variable, t_env *env)
{
	t_env	*node;
	char *key;
	char *value;
	
	if(!new_variable)
		print_export(env);
	if(check_spaces(new_variable))
		return ;
	formate_env_item(&key, &value, new_variable);
	node = ft_new_node(key, value);
	if (node)
			ft_add_back_env(&env, node); 
	add_to_env(new_variable, env);
}
