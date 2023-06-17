/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utlis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:19:06 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/17 13:24:25 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_digits(char *data)
{
	int	index;

	index = 0;
	while (data[index])
	{
		if (!ft_isdigit(data[index]))
			return (1);
		index++;
	}
	return (0);
}

void	print_env(t_env	*env, int out)
{
	while (env)
	{
		if (env->key && env->value && ft_strncmp(env->key, "_", 2))
		{
			ft_putstr_fd("declare -x ", out);
			ft_putstr_fd(env->key, out);
			ft_putstr_fd("=\"", out);
			ft_putstr_fd(env->value, out);
			ft_putendl_fd("\"", out);
		}
		else if (env->key && !env->value)
		{
			ft_putstr_fd("declare -x ", out);
			ft_putendl_fd(env->key, out);
		}
		env = env->next;
	}
}

void	print_export(t_env *env, int out)
{
	t_env	*cur;
	t_env	*tmp;
	char	*key;
	char	*value;

	cur = env;
	while (cur)
	{
		tmp = cur->next;
		while (tmp)
		{
			if (tmp->key[0] < cur->key[0])
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
	print_env(env, out);
}
