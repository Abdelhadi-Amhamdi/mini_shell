/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:23:03 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/15 13:29:01 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_list *env)
{
	t_list	*tmp;
	char	*content;

	tmp = env;
	// print envirenment variables in stdout
	while (tmp)
	{
		content = (char *)(tmp->content);
		ft_putendl_fd(content, 1);
		tmp = tmp->next;
	}
}
