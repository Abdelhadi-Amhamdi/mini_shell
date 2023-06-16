/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:18:29 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/16 11:33:38 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*ft_sub_str(char *str, int start, int len)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	while (str[start] && i < len)
	{
		if (str[start] != '\\')
			s[i] = str[start];
		i++;
		start++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_search(char *item, char tofind)
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

	index = ft_search(item, '=');
	if (index != -1)
	{
		*key = ft_sub_str(item, 0, index);
		*val = ft_sub_str(item, index + 1, (ft_strlen(item) - index));
	}
	else
	{
		*key = ft_strdup(item);
		*val = NULL;
	}
}

void	add_oldpwd(t_env **envp)
{
	t_env	*oldpwd;
	t_env	*new;

	oldpwd = ft_search_env(*envp, "OLDPWD");
	if (!oldpwd)
	{
		new = ft_new_node("OLDPWD", NULL);
		ft_add_back_env(envp, new);
	}
}

t_env	*get_env_vars(char **envp)
{
	t_env	*env;
	t_env	*node;
	int		index;
	char	*key;
	char	*value;
	int		v;

	env = NULL;
	index = 0;
	while (envp[index])
	{
		value = NULL;
		key = NULL;
		formate_env_item(&key, &value, envp[index]);
		if (!ft_strncmp(key, "SHLVL", ft_strlen(key)))
		{
			v = ft_atoi(value);
			v++;
			free(value);
			value = ft_itoa(v);
		}
		node = ft_new_node(key, value);
		if (node)
			ft_add_back_env(&env, node);
		index++;
	}
	add_oldpwd(&env);
	return (env);
}
