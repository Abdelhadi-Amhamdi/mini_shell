/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:18:29 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/22 09:09:23 by aagouzou         ###   ########.fr       */
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
		if (item[ft_strlen(item) - 1] == '+')
		{
			*key = NULL;
		}
		else
			*key = ft_strdup(item);
		*val = NULL;
	}
}

void	add_oldpwd(t_env **envp)
{
	t_env	*oldpwd;
	t_env	*pwd;
	t_env	*new;

	oldpwd = ft_search_env(*envp, "OLDPWD");
	pwd = ft_search_env(*envp, "PWD");
	if (!oldpwd)
	{
		new = ft_new_node(ft_strdup("OLDPWD"), NULL);
		ft_add_back_env(envp, new);
	}
	if (!pwd)
	{
		new = ft_new_node(ft_strdup("PWD"), getcwd(NULL, 0));
		ft_add_back_env(envp, new);
	}
}

void	set_shlvl(char **value)
{
	int	old_value;

	old_value = ft_atoi(*value);
	old_value++;
	free(*value);
	*value = ft_itoa(old_value);
}

t_env	*get_env_vars(char **envp)
{
	t_env	*env;
	t_env	*node;
	int		index;
	char	*key;
	char	*value;

	env = NULL;
	index = 0;
	if (!(*envp))
		set_important_vars(&env);
	while (envp[index])
	{
		value = NULL;
		key = NULL;
		formate_env_item(&key, &value, envp[index]);
		if (!ft_strncmp(key, "SHLVL", ft_strlen(key)))
			set_shlvl(&value);
		node = ft_new_node(key, value);
		if (node)
			ft_add_back_env(&env, node);
		index++;
	}
	add_oldpwd(&env);
	return (env);
}
