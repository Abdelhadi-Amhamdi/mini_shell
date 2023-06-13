/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:23:03 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/13 19:11:44 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	ft_env(t_env *env, int out)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if(tmp->key && tmp->value)
		{
			ft_putstr_fd(tmp->key, out);
			ft_putstr_fd("=", out);
			ft_putendl_fd(tmp->value, out);
		}
		tmp = tmp->next;
	}
	return (0);
}
