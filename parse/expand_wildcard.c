/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:52:16 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/16 20:52:54 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_lexer	*create_list(char **tabs)
{
	int		index;
	t_lexer	*list;
	t_lexer	*new_node;

	index = 0;
	list = NULL;
	while (tabs[index])
	{
		new_node = create_token(tabs[index], ft_strlen(tabs[index]), NULL);
		new_node->type = ARGS;
		new_node->path = NULL;
		add_token_to_end(&list, new_node);
		index++;
	}
	return (list);
}

t_lexer	*get_last_token(t_lexer *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_expand_wildcards(t_lexer **list)
{
	t_lexer	*tmp;
	t_lexer	*last;
	t_lexer	*new_list;
	char	*data;
	char	**tabs;
	int		index;

	index = 0;
	tmp = *list;
	while (tmp)
	{
		if (tmp->type == WILDCARD)
		{
			data = wildcard(tmp->str);
			if (!data || !*data)
				return ;
			tabs = ft_split(data, 32);
			if (!tabs)
				puts("split error");
			new_list = create_list(tabs);
			last = get_last_token(new_list);
			last->next = tmp->next;
			tmp->prev->next = new_list;
			del_node(tmp);
			ft_free(tabs);
			free(data);
			data = NULL;
			tmp = last->next;
		}
		else
			tmp = tmp->next;
	}
}