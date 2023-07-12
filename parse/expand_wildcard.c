/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:52:16 by aagouzou          #+#    #+#             */
/*   Updated: 2023/07/11 08:48:52 by aamhamdi         ###   ########.fr       */
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
		new_node->type = UNK;
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

t_lexer	*expand_wildcards_helper(t_lexer *tmp)
{
	char	*data;
	char	**tabs;
	t_lexer	*new_list;

	new_list = NULL;
	data = wildcard(tmp->str);
	if (!data || !*data)
		return (NULL);
	tabs = ft_split(data, 32);
	free(data);
	if (!tabs)
		return (NULL);
	new_list = create_list(tabs);
	ft_free(tabs);
	return (new_list);
}

int	ft_expand_wildcards(t_lexer **list)
{
	t_lexer	*tmp;
	t_lexer	*last;
	t_lexer	*new_list;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == WILDCARD)
		{
			new_list = expand_wildcards_helper(tmp);
			if (!new_list)
				return (1);
			if (tmp->prev && (tmp->prev->type == RDIR || tmp->prev->type \
			== APND) && _args_size(new_list) > 1)
				return (p_error(AME, tmp, 1), _free_lexer(&new_list), 1);
			last = get_last_token(new_list);
			last->next = tmp->next;
			re_link_list(tmp, new_list, list);
			del_node(tmp);
			tmp = last->next;
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

void	set_null_value(t_lexer	*tmp)
{
	char	*temp;

	temp = tmp->str;
	tmp->str = NULL;
	free(temp);
}
