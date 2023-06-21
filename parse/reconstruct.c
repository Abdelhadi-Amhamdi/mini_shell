/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:33:35 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/21 17:57:55 by aagouzou         ###   ########.fr       */
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
	char	*data;
	int		index;

	tmp = list;
	while (tmp)
	{
		if (tmp->str[0] == '"' || tmp->str[0] == '\'')
		{
			index = 0;
			data = tmp->str;
			current = data[index];
			while (data[++index] && data[index] != current);
			if (!data[index])
				return (ft_putendl_fd(QUOTES_ERROR_MSG, 2), 1);
			ft_trim_quotes(tmp);
		}
		else if (tmp->type == HEREDOC)
		{
			tmp = tmp->next;
			if (tmp && (tmp->str[0] == '"' || tmp->str[0] == '\''))
			{
				index = 0;
				data = tmp->str;
				current = data[index];
				while (data[++index] && data[index] != current);
				if (!data[index])
					return (ft_putendl_fd(QUOTES_ERROR_MSG, 2), 1);
				ft_trim_quotes(tmp);
				tmp->is_builtin = 0;
			}
			else if (tmp)
				tmp->is_builtin = 1;
			else
				break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

// check if the node need to be joined with the next node
int	to_join(t_lexer *node)
{
	if (node && !node->is_oper && node->type != W_SPACE && \
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
		if (to_join(tmp) && to_join(tmp->next))
		{
			str_tmp = tmp->str;
			next_tmp = tmp->next;
			tmp->str = ft_strjoin(tmp->str, tmp->next->str);
			if (!tmp->str)
				return ;
			free(str_tmp);
			tmp->path = get_path(tmp->str, paths);
			tmp->type = check_type(tmp, tmp->path);
			tmp->next = tmp->next->next;
			
			del_node(next_tmp);
		}
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
