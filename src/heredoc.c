/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/26 15:02:09 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
#include "../libs/gnl/get_next_line.h"

# define DOC_FILE "heredoc_file"

t_h_list *create_heredoc_node(char *str)
{
	t_h_list	*new_node;

	new_node = malloc(sizeof(t_h_list));
	if (!new_node)
		return (NULL);
	new_node->data = str;
	new_node->next = NULL;
	return (new_node);
}

void heredoc_list_add(t_h_list **list, t_h_list *item)
{
	t_h_list *tmp;
	
	tmp = NULL;
	if (!(*list))
		*list = item;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = item;
	}
}

int	herdoc(char *delemiter, t_app *app)
{
	char	*line;
	t_h_list	*new_node;

	app->herdoc_list = NULL;
	write(0, "> ", 2);
	line = get_next_line(0);
	while (1)
	{
		new_node = create_heredoc_node(line);
		if (!new_node)
			return (-1);
		heredoc_list_add(&(app->herdoc_list), new_node);
		free(line);
		write(0, "> ", 2);
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, delemiter, (ft_strlen(line) - 1)))
			break ;
	}
	free (line);
	return (0);
}
