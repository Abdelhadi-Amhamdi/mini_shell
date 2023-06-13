/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/12 18:18:29 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
#include "../libs/gnl/get_next_line.h"

char *start_heredoc(t_lexer *node, t_boolean to_expand)
{
	char	*line;
	char	*del;
	char 	*file_name;
	char *res;
	
	file_name = ft_strjoin(HEREDOC_FILENAME, ft_itoa(node->id));
	del = node->next->str;
	app->hdoc_fd = open(file_name, O_CREAT | O_RDWR, 0644);
	if (app->hdoc_fd == -1)
		return (NULL);
	write(0, "> ", 2);
	line = get_next_line(0);
	while (1)
	{
		if(to_expand && line[0] == '$')
		{
			line[strlen(line) - 1] = '\0';
			res = expand(line, app->env_list, 0);
			if (res && *res)
				ft_putendl_fd(res, app->hdoc_fd);
		}
		else
			ft_putstr_fd(line, app->hdoc_fd);
		free(line);
		write(0, "> ", 2);
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, del, (ft_strlen(line) - 1)))
			break ;
	}
	free (line);
	close(app->hdoc_fd);
	return (file_name);
}

// int	herdoc(t_tree *hrd)
// {
// 	char	*line;
// 	char	*del;
// 	t_tree	*cmd;

// 	del = hrd->right->str;
// 	cmd = hrd->left;
// 	app->hdoc_fd = open(HEREDOC_FILENAME, O_CREAT | O_RDWR, 0644);
// 	write(0, "> ", 2);
// 	line = get_next_line(0);
// 	while (1)
// 	{
// 		ft_putstr_fd(line, app->hdoc_fd);
// 		free(line);
// 		write(0, "> ", 2);
// 		line = get_next_line(0);
// 		if (!line || !ft_strncmp(line, del, (ft_strlen(line) - 1)))
// 			break ;
// 	}
// 	free (line);
// 	close(app->hdoc_fd);
// 	app->hdoc_fd = open(HEREDOC_FILENAME, O_RDONLY, 0644);
// 	if (app->hdoc_fd == -1)
// 		return (ft_putendl_fd("Error", 2), -1);
// 	if (cmd)
// 	{
// 		exec_cmd(cmd, -1, app->hdoc_fd, 0, -1);
// 		close(app->hdoc_fd);
// 		wait(NULL);
// 	}
// 	unlink(HEREDOC_FILENAME);
// 	return (0);
// }
