/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/24 19:04:05 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
#include "../libs/gnl/get_next_line.h"

# define DOC_FILE "heredoc_file"

void	herdoc(char *delemiter)
{
	char	*line;
	int		fd;

	fd = open(DOC_FILE, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return ;
	write(0, "> ", 2);
	line = get_next_line(0);
	while (1)
	{
		free(line);
		ft_putstr_fd(line, fd);
		write(0, "> ", 2);
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, delemiter, (ft_strlen(line) - 1)))
			break ;
	}
	free (line);
	close(fd);
	unlink(DOC_FILE);
}
