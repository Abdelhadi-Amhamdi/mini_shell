/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:57:36 by aagouzou          #+#    #+#             */
/*   Updated: 2023/05/30 18:33:16 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_path(char *cmd, char **paths)
{
	char	*command;
	char	*full_path;
	int		index;

	command = ft_strjoin("/", cmd);
	index = 0;
	if (!command)
		return (NULL);
	while (paths[index])
	{
		full_path = ft_strjoin(paths[index], command);
		if (!full_path)
			return (free(command), NULL);
		if (!access(full_path, F_OK | X_OK))
			return (free(command), full_path);
		free(full_path);
		index++;
	}
	free(command);
	return (NULL);
}

int	is_file(t_lexer *node)
{
	
	if (!ft_strncmp((node->str + (ft_strlen(node->str) - 4)), ".txt", 4))
		return (1);
	if (node->str[0] != ' ' && node->str[0] != ')' && node->str[0] != '(' && node->prev && (node->prev->type == RDIR || \
	node->prev->type == APND || node->prev->type == HEREDOC))
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "pwd", 3)
		|| !ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "exit", 4)
		|| !ft_strncmp(cmd, "env", 3))
		return (1);
	return (0);
}

int	is_var(t_lexer *node)
{
	int	s_count;
	int	d_count;

	s_count = 0;
	d_count = 0;
	while (node)
	{
		if (node->is_oper && node->str[0] == '\'')
			s_count++;
		if (node->is_oper && node->str[0] == '"')
			d_count++;
		node = node->prev;
	}
	if ((s_count % 2) && !(d_count % 2))
		return (0);
	return (1);
}

int ft_char_search(char *str, char c)
{
	int index;

	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

int ft_last_char_search(char *str, char c)
{
	int index;

	index = ft_strlen(str) - 1;
	while (index >= 0)
	{
		if (str[index] == c)
			return (index);
		index--;
	}
	return (-1);
}

int is_wild_card(t_lexer *node)
{
	if (node->str[0] != '"' && node->str[0] != '\'' \
	&& ft_char_search(node->str, '*') != -1)
		return (1);
	return (0);
}


// check the type of the given arg
t_type	check_type(t_lexer *node, char *path)
{
	if (is_file(node))
		return (FL);
	else if ((path || is_builtin(node->str)))
		return (CMD);
	else if (is_wild_card(node))
		return (WILDCARD);
	else if (node->str[0] == '\'')
		return (SQ);
	else if (node->str[0] == '"')
		return (DQ);
	else if (node->str[0] == '(')
		return (OP);
	else if (node->str[0] == ')')
		return (CP);
	else if (node->is_oper && !compare(node, "|"))
		return (PIPE);
	else if (node->is_oper && !compare(node, "&&"))
		return (AND);
	else if (node->is_oper && !compare(node, "||"))
		return (OR);
	else if (node->is_oper && !compare(node, ">"))
		return (RDIR);
	else if (node->is_oper && !compare(node, ">>"))
		return (APND);
	else if (node->is_oper && !compare(node, "<<"))
		return (HEREDOC);
	else if (node->str[0] == '$' && is_var(node->prev))
		return (VAR);
	else if (node->str[0] == '-')
		return (ARGS);
	else if (node->str[0] == 32)
		return (SPACE);
	return (UNK);
}
