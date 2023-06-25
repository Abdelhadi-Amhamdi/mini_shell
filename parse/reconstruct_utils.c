/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:14:12 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/25 16:25:29 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	check_and_trim(t_lexer *tmp, char **paths)
{
	int		index;
	char	*data;
	char	current;

	index = 1;
	data = tmp->str;
	current = data[index];
	while (data[index] && data[index] != current)
		index++;
	if (!data[index])
		return (ft_putendl_fd(QUOTES_ERROR_MSG, 2), 1);
	ft_trim_quotes(tmp);
	if (tmp->str && *tmp->str && paths)
		tmp->path = get_path(tmp->str, paths);
	return (0);
}

void	_rebuild_node(t_lexer *tmp, char **paths)
{
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
