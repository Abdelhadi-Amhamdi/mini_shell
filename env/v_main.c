/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:18:29 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/05 16:40:31 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int ft_search(char *item, char tofind)
{
	int	index;

	index = 0;
	while (item[index])
	{
		if (item[index] == tofind)
			return (index);
		index++;
	}
	return (-1);
}

void	formate_env_item(char **key, char **val, char *item)
{
	int	index;

	index = ft_search(item , '=');
	*key = ft_substr(item, 0, index);
	*val = ft_substr(item, index + 1, (ft_strlen(item) - index));
}

t_env	*get_env_vars(char **envp)
{
	t_env	*env ;
	t_env	*node;
	int		index;
	char	*key;
	char	*value;

	env = NULL;
	index = 0;
	while (envp[index])
	{
		value = NULL;
		key = NULL;
		formate_env_item(&key, &value, envp[index]);
		node = ft_new_node(key, value);
		if (node)
			ft_add_back_env(&env, node);
		index++;
	}
	return (env);
}
