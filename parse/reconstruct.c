/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:33:35 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/23 23:14:51 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

// get rid of quotes and check if the arg are empty
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

// check if the quotes are closed and get rid of them
int	check_qoutes(t_lexer *list)
{
	t_lexer	*tmp;
	char	current;

	tmp = list;
	while (tmp)
	{
		if (tmp->str[0] == '"' || tmp->str[0] == '\'')
			check_and_trim(tmp);
		else if (tmp->type == HEREDOC)
		{
			tmp = tmp->next;
			if (tmp && (tmp->str[0] == '"' || tmp->str[0] == '\''))
			{
				check_and_trim(tmp);
				tmp->is_builtin = 0;
			}
			else
				tmp->is_builtin = 1;
		}
		tmp = tmp->next;
	}
	return (0);
}

// check if the node need to be joined with the next node
int	to_join(t_lexer *node)
{
	if (node && strchr(node->str, '$') && node->type == UNK)
		node->id = DONT_EXPAND;
	if (node && !node->is_oper && (node->type != W_SPACE || node->id == -14) && \
		node->type != OP && node->type != CP && *node->str)
		return (1);
	return (0);
}

// join args that no space or operator between them
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
			_rebuild_node(tmp, paths);
			tmp->next = tmp->next->next;
			del_node(next_tmp);
		}
		else
			tmp = tmp->next;
	}
}

int	check_pths(t_lexer *list)
{
	int	op;
	int	cp;

	op = 0;
	cp = 0;
	while (list)
	{
		if (list->type == OP)
			op++;
		else if (list->type == CP)
			cp++;
		list = list->next;
		if (op - cp < 0)
			break ;
	}
	if (op - cp != 0)
		return (ft_putendl_fd(PARENTICIES_ERROR_MSG, 2), 1);
	return (0);
}
