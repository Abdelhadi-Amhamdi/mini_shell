/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/24 17:20:43 by aamhamdi         ###   ########.fr       */
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
	write(0, "heredoc > ", 10);
	line = get_next_line(0);
	ft_putstr_fd(line, fd);
	while (1)
	{
		write(0, "heredoc > ", 10);
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, delemiter, (ft_strlen(line) - 1)))
			break ;
		ft_putstr_fd(line , fd);
	}
	close(fd);
	fd = open(DOC_FILE, O_RDONLY, 0644);
	line = get_next_line(fd);
	ft_putstr_fd(line, 1);
	while (line)
	{
		line = get_next_line(fd);
		ft_putstr_fd(line, 1);
	}
	close (fd);
	unlink(DOC_FILE);
}
