/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/05 13:21:21 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*expand(char *var, char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (!ft_strncmp(var, envp[index], ft_strlen(var)))
			return ((envp[index] + (ft_strlen(var) + 1)));
		index++;
	}
	return (NULL);
}

void	ft_expander(t_parser *list, char **envp)
{
	t_parser	*tmp;
	char		*val;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == TOKEN && tmp->str[0] == '$')
		{
			val = expand(tmp->next->str, envp);
			tmp->next->str = val;
			tmp->next->type = VAR;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}
