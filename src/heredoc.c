/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/06 16:36:15 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
#include "../libs/gnl/get_next_line.h"

# define DOC_FILE "heredoc_file"

// void ft_free_heredoc_list(t_h_list **list)
// {
// 	t_h_list *tmp;
// 	t_h_list *next;

// 	tmp = *list;
// 	while (tmp)
// 	{
// 		next = tmp->next;
// 		free(tmp);
// 		tmp = next;
// 	}
// 	*list = NULL;
// }

// t_h_list *create_heredoc_node(char *str)
// {
// 	t_h_list	*new_node;

// 	new_node = malloc(sizeof(t_h_list));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->data = str;
// 	new_node->next = NULL;
// 	return (new_node);
// }

// void heredoc_list_add(t_h_list **list, t_h_list *item)
// {
// 	t_h_list *tmp;
	
// 	tmp = NULL;
// 	if (!(*list))
// 		*list = item;
// 	else
// 	{
// 		tmp = *list;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = item;
// 	}
// }

int	herdoc(t_tree *hrd)
{
	char	*line;
	char	*del;
	t_tree	*cmd;

	del = hrd->right->str;
	cmd = hrd->left;
	app->hdoc_fd = open(HEREDOC_FILENAME, O_CREAT | O_RDWR, 0644);
	write(0, "> ", 2);
	line = get_next_line(0);
	while (1)
	{
		ft_putstr_fd(line, app->hdoc_fd);
		free(line);
		write(0, "> ", 2);
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, del, (ft_strlen(line) - 1)))
			break ;
	}
	free (line);
	close(app->hdoc_fd);
	app->hdoc_fd = open(HEREDOC_FILENAME, O_RDONLY, 0644);
	if (app->hdoc_fd == -1)
		return (ft_putendl_fd("Error", 2), -1);
	if (cmd)
	{
		exec_cmd(cmd, -1, app->hdoc_fd, 0, -1);
		close(app->hdoc_fd);
		wait(NULL);
	}
	unlink(HEREDOC_FILENAME);
	return (0);
}
