/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:26:37 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/15 13:27:34 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(char *var_name, t_list **env)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *env;
	prev = NULL;
	// search for the given variable and delete it from the env list
	while (tmp)
	{
		if (!ft_strncmp(var_name, tmp->content, ft_strlen(var_name)))
		{
			if (!prev)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			tmp->content = NULL;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
