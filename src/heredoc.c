/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/06 16:46:47 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
#include "../libs/gnl/get_next_line.h"

# define DOC_FILE "heredoc_file"

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
