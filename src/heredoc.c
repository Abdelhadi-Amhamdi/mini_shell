/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/16 22:06:18 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*ft_read_line(int fd)
{
	char	*line;

	write(fd, "> ", 2);
	line = get_next_line(fd);
	return (line);
}

char	*wait_heredoc(char *file_name, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (status)
	{
		unlink(file_name);
		exit_status = EXIT_SUCCESS;
		return (NULL);
	}
	exit_status = EXIT_SUCCESS;
	return (file_name);
}

int	run_heredoc(char *del, t_boolean to_expand, int fd, t_main *data)
{
	char	*line;
	char	*res;

	line = ft_read_line (STDIN_FILENO);
	while (1)
	{
		if (!line)
			return (EXIT_FAILURE);
		del[ft_strlen (del)] = '\n';
		if (!ft_strncmp (line, del, (ft_strlen(line))))
			return (EXIT_SUCCESS);
		if (to_expand && line[0] == '$')
		{
			line[strlen (line) - 1] = '\0';
			res = expand (line, data->env, 0);
			if (res && *res)
				ft_putendl_fd (res, fd);
		}
		else
			ft_putstr_fd (line, fd);
		free (line);
		line = ft_read_line (STDIN_FILENO);
	}
	close (fd);
	return (free (line), EXIT_SUCCESS);
}

char	*start_heredoc(t_lexer *node, t_boolean to_expand, t_main *data)
{
	char	*file_name;
	char	*char_id;
	int		fd;
	pid_t	pid;

	char_id = ft_itoa(node->id);
	file_name = ft_strjoin(HEREDOC_FILENAME, char_id);
	free(char_id);
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, sigint_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
		exit (run_heredoc(node->next->str, to_expand, fd, data));
	}
	else
		exit_status = -1;
	close(fd);
	return (wait_heredoc(file_name, pid));
}
