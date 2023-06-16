/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/16 11:12:05 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*start_heredoc(t_lexer *node, t_boolean to_expand, t_main *data)
{
	char	*line;
	char	*del;
	char	*file_name;
	char	*res;
	char	*id;
	int		status;
	int		fd;
	int		pid;

	id = ft_itoa(node->id);
	file_name = ft_strjoin(HEREDOC_FILENAME, id);
	free(id);
	del = node->next->str;
	fd = open(file_name, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (NULL);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, sigint_heredoc_handler);
		signal(SIGQUIT, SIG_DFL);
		write(0, "> ", 2);
		line = get_next_line(0);
		while (1)
		{
			if (!line)
			{
				status = 0;
				break ;
			}
			del[ft_strlen(del)] = '\n';
			if (!ft_strncmp(line, del, (ft_strlen(line))))
			{
				status = 1;
				break ;
			}
			if (to_expand && line[0] == '$')
			{
				line[strlen(line) - 1] = '\0';
				res = expand(line, data->env, 0);
				if (res && *res)
					ft_putendl_fd(res, fd);
			}
			else
				ft_putstr_fd(line, fd);
			free(line);
			write(0, "> ", 2);
			line = get_next_line(0);
		}
		free (line);
		close(fd);
		exit (status);
	}
	else
		exit_status = -1;
	close(fd);
	waitpid(pid, &status, 0);
	if (!status)
	{
		unlink(file_name);
		exit_status = 1;
		return (NULL);
	}
	exit_status = 0;
	return (file_name);
}
