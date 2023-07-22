/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:45:53 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/22 09:07:20 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_variables(t_lexer *list)
{
	char	*temp;
	t_lexer	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->str[0] == '$' && ft_strlen(tmp->str) == 1 && (tmp->next
				&& (tmp->next->type == SQ || tmp->next->type == DQ)))
		{
			temp = tmp->str;
			tmp->str = ft_strdup("");
			free(temp);
		}
		tmp = tmp->next;
	}
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}
