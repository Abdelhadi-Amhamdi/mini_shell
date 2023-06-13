/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/13 18:50:13 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
#include "../libs/gnl/get_next_line.h"

void sigint_heredoc_handler()
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit (0);
}


char *start_heredoc(t_lexer *node, t_boolean to_expand, t_main *data)
{
	char	*line;
	char	*del;
	char 	*file_name;
	char	*res;
	char 	*id;
	int		status;
	int fd;
	
	id = ft_itoa(node->id);
	file_name = ft_strjoin(HEREDOC_FILENAME, id);
	free(id);
	del = node->next->str;
	fd = open(file_name, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (NULL);
	int pid = fork();
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
			else if (!ft_strncmp(line, del, (ft_strlen(line) - 1)))
			{
				status = 1;
				break;
			}
			if(to_expand && line[0] == '$')
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
	// printf("%d\n", status);
	if (!status)
		return (NULL);
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
