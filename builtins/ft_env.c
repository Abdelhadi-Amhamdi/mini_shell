/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:23:03 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/07 18:29:13 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	// print envirenment variables in stdout
	while (tmp)
	{
		printf("%s=%s\n",tmp->key,tmp->value);
		tmp = tmp->next;
	}
}
