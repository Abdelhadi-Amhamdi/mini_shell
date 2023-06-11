/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:18:29 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/11 15:09:44 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./env.h"

char *ft_sub_str(char *str, int start, int len)
{
	int i;
	char *s;

	i = 0;
	s = malloc (len + 1);
	if(!s)
		return(NULL);
	while(str[start] && i < len)
	{
		if(str[start] != '\\')
			s[i] = str[start];
		i++;
		start++;
	}
	s[i] = '\0';
	return(s);
}

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
	*key = ft_sub_str(item, 0, index);
	if(index != -1)
		*val = ft_sub_str(item, index + 1, (ft_strlen(item) - index));
	else
		*val = NULL;
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
		if (!ft_strncmp(key, "SHLVL", ft_strlen(key)))
		{
			int v = ft_atoi(value);
			v++;
			free(value);
			value = ft_itoa(v);
		}
		node = ft_new_node(key, value);
		if (node)
			ft_add_back_env(&env, node);
		index++;
	}
	return (env);
}
