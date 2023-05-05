/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/05 16:19:33 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*expand(char *var, t_env *envp)
{
	int	index;

	index = 0;
	while (envp)
	{
		if (!ft_strncmp(var, envp->key, ft_strlen(var)))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

void	ft_expander(t_parser *list, t_env *envp)
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
