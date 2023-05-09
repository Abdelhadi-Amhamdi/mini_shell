/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:26:37 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/08 18:48:45 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_unset(char *var_name, t_env **env)
{
	(void	)env;
	printf("%s\n",var_name);
	// t_list	*tmp;
	// t_list	*prev;

	// tmp = *env;
	// prev = NULL;
	// // search for the given variable and delete it from the env list
	// while (tmp)
	// {
	// 	if (!ft_strncmp(var_name, tmp->content, ft_strlen(var_name)))
	// 	{
	// 		if (!prev)
	// 			*env = tmp->next;
	// 		else
	// 			prev->next = tmp->next;
	// 		tmp->content = NULL;
	// 		free(tmp);
	// 		return ;
	// 	}
	// 	prev = tmp;
	// 	tmp = tmp->next;
	// }
}
