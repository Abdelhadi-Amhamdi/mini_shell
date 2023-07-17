/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:33:35 by aagouzou          #+#    #+#             */
/*   Updated: 2023/07/17 16:10:19 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_trim_quotes(t_lexer *node)
{
	t_lexer	*tmp;
	char	*str_tmp;

	tmp = node;
	if (!tmp)
		return ;
	str_tmp = tmp->str;
	if (tmp->str[0] == '\'')
		tmp->str = ft_strtrim(tmp->str, "'");
	else if (tmp->str[0] == '"')
		tmp->str = ft_strtrim(tmp->str, "\"");
	free(str_tmp);
}

void	check_del(t_lexer *tmp)
{
	if (tmp->next && \
	(*tmp->next->str == '\'' || *tmp->next->str == '"'))
		tmp->is_builtin = 0;
	else if (tmp->prev && \
	(*tmp->prev->str == '\'' || *tmp->prev->str == '"'))
		tmp->is_builtin = 0;
	else
		tmp->is_builtin = 1;
}

int	check_qoutes(t_lexer *list, char **paths)
{
	t_lexer	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->str[0] == '"' || tmp->str[0] == '\'')
		{
			if (check_and_trim(tmp, paths))
				return (1);
		}
		else if (tmp->type == HEREDOC)
		{
			if (tmp->next && \
			(tmp->next->str[0] == '"' || tmp->next->str[0] == '\''))
			{
				if (check_and_trim(tmp->next, NULL))
					return (1);
				tmp->next->is_builtin = 0;
			}
			else if (tmp->next)
				check_del(tmp->next);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	to_join(t_lexer *node)
{
	if (node && strchr(node->str, '$') && node->type == UNK)
		node->id = DONT_EXPAND;
	if (node && !node->is_oper && (node->type != W_SPACE || node->id == -14) && \
		node->type != OP && node->type != CP)
		return (1);
	return (0);
}

void	join_args(t_lexer **list, char **paths)
{
	t_lexer	*tmp;
	t_lexer	*next_tmp;
	char	*str_tmp;

	tmp = *list;
	while (tmp)
	{
		if (to_join(tmp) && tmp->next && to_join(tmp->next))
		{
			str_tmp = tmp->str;
			next_tmp = tmp->next;
			tmp->str = ft_strjoin(tmp->str, tmp->next->str);
			if (!tmp->str)
				return ;
			free(str_tmp);
			_rebuild_node(tmp, paths);
			if (tmp->next && tmp->next->next)
				tmp->next->next->prev = tmp;
			tmp->next = tmp->next->next;
			del_node(next_tmp);
		}
		else
			tmp = tmp->next;
	}
}
