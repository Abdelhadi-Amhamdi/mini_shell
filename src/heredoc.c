/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:17:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/07 22:52:36 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
#include "../libs/gnl/get_next_line.h"

void heredoc_handler(t_lexer **list)
{
	t_lexer *tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (!tmp->prev)
				*list = heredoc_helper(tmp);
			else
				tmp->prev->next = heredoc_helper(tmp);
		}
		tmp = tmp->next;
	}	
}

t_lexer *get_hlast_token(t_lexer *root)
{
	t_lexer *tmp;

	tmp = root->prev;
	while (tmp && !tmp->is_oper)
	{
		if (tmp->type == CMD)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

t_lexer *get_next_token(t_lexer *root)
{
	t_lexer *tmp;

	tmp = root->next;
	while (tmp && !tmp->is_oper)
	{
		if (tmp->type == CMD)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

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
			res = expand(line+1, app->env_list);
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

t_lexer  *heredoc_helper(t_lexer *root)
{
	t_lexer *next;
	t_lexer *prev;
	t_lexer *tmp;
	char *file_name;

	prev = get_hlast_token(root);
	next = get_next_token(root);
	file_name = start_heredoc(root, !root->next->is_builtin);
	if (next && prev)
	{
		unlink(file_name);
		prev->next = next;
		del_node(root->next);
		del_node(root);
		return (next);
	}
	else
	{
		tmp = ft_nodedup(root);
		tmp->str = file_name;
		tmp->path = file_name;
		tmp->is_oper = FALSE;
		tmp->type = FL;
		if (next)
		{
			tmp->next = next->next;
			next->next = tmp;
			del_node(root->next);
			del_node(root);
			return (next);
		}
		else if (prev)
		{
			tmp->next = root->next->next;
			del_node(root->next);
			del_node(root);
			return (tmp);
		}
	}
	if (!next && !prev)
		unlink(file_name);
	del_node(root->next);
	del_node(root);
	return (NULL);
}

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
