/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:14:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/23 23:15:11 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	check_and_trim(t_lexer *tmp)
{
	int		index;
	char	*data;

	index = 1;
	data = tmp->str;
	current = data[index];
	while (data[index] && data[index] != current)
		index++;
	if (!data[index])
		return (ft_putendl_fd(QUOTES_ERROR_MSG, 2), 1);
	ft_trim_quotes(tmp);
}

void	_rebuild_node(t_lexer *tmp, char **paths)
{
	free(str_tmp);
	if (tmp->path)
		free(tmp->path);
	tmp->path = get_path(tmp->str, paths);
	tmp->type = check_type(tmp, tmp->path);
	if ((tmp->type == SQ && tmp->next->type == VAR) \
	|| (tmp->type == VAR && tmp->next->type == SQ))
		tmp->type = VAR;
	if (tmp->next->id == DONT_EXPAND)
		tmp->id = DONT_EXPAND;
}
