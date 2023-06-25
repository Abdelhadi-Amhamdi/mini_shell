/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/25 18:04:07 by aamhamdi         ###   ########.fr       */
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
		g_exit_status = EXIT_SUCCESS;
		free (file_name);
		return (NULL);
	}
	g_exit_status = EXIT_SUCCESS;
	return (file_name);
}

void	ft_write_infile(t_lexer *list, char *file_name)
{
	int		fd;
	t_lexer	*tmp;

	tmp = list;
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	while (tmp)
	{
		if (tmp->type == UNK)
			ft_putstr_fd(tmp->str, fd);
		else
			ft_putendl_fd(tmp->str, fd);
		tmp = tmp->next;
	}
	close(fd);
	_free_lexer(&list);
}

int	run_heredoc(char *del, t_boolean to_expand, char *file_name, t_main *data)
{
	char		*line;
	t_lexer		*content;

	content = NULL;
	line = ft_read_line (STDIN_FILENO);
	while (1)
	{
		if (!line)
			return (EXIT_FAILURE);
		del[ft_strlen (del)] = '\n';
		if (!ft_strncmp (line, del, (ft_strlen(line))))
			break ;
		if (to_expand && ft_strchr(line, '$'))
		{
			line[strlen (line) - 1] = '\0';
			_add_doc_to_end(&content, _create_doc(line, VAR));
		}
		else
			_add_doc_to_end(&content, _create_doc(line, UNK));
		free (line);
		line = ft_read_line (STDIN_FILENO);
	}
	ft_expand_vars(&content, data->env, content);
	ft_write_infile(content, file_name);
	return (free (line), EXIT_SUCCESS);
}

char	*start_heredoc(t_lexer *node, t_boolean to_expand, t_main *data)
{
	char	*file_name;
	char	*char_id;
	pid_t	pid;

	char_id = ft_itoa(node->id);
	file_name = ft_strjoin(HEREDOC_FILENAME, char_id);
	free(char_id);
	pid = _ft_fork();
	if (pid == -1)
		return (free (file_name), NULL);
	if (!pid)
	{
		signal(SIGINT, sigint_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
		exit (run_heredoc(node->next->str, to_expand, file_name, data));
	}
	else
		g_exit_status = -1;
	return (wait_heredoc(file_name, pid));
}
