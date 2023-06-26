/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:16:43 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/26 09:27:25 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	compare(t_lexer *item, char *oper)
{
	return (ft_strncmp(item->str, oper, ft_strlen(item->str)));
}

int	is_file(t_lexer *node)
{
	if (!node->is_oper && node->str[0] != ' ' && node->str[0] != ')'
		&& node->str[0] != '(' && node->str[0] != '>' && node->prev
		&& node->str[0] != '$' && ((node->prev->type == RDIR \
		|| node->prev->type == APND) && \
		(node->type == DQ || node->type == SQ || node->str[0] != '*')))
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "exit", 5)
		|| !ft_strncmp(cmd, "env", 4))
		return (1);
	return (0);
}

t_type	rest_of_types(t_lexer *node)
{
	if (node->is_oper && !compare(node, "|"))
		return (PIPE);
	else if (node->is_oper && !compare(node, "&&"))
		return (AND);
	else if (node->is_oper && !compare(node, "||"))
		return (OR);
	else if (node->is_oper && (!compare(node, ">") || !compare(node, "<")))
		return (RDIR);
	else if (node->is_oper && !compare(node, ">>"))
		return (APND);
	else if (node->is_oper && !compare(node, "<<"))
		return (HEREDOC);
	else if (is_all_space(node->str) && *node->str)
		return (W_SPACE);
	return (UNK);
}

// check the type of the given arg
t_type	check_type(t_lexer *node, char *path)
{
	if (node && node->type == VAR && node->str[0] == '\'')
		return (VAR);
	else if (is_file(node))
		return (FL);
	else if ((path || is_builtin(node->str)))
		return (CMD);
	else if (ft_strchr(node->str, '$') && node->type != SQ \
	&& node->str[0] != '\'' && node->prev \
	&& node->prev->type != HEREDOC && node->type != SQ)
		return (VAR);
	else if (node->str[0] == '*' && node->type != SQ && node->type != DQ)
		return (WILDCARD);
	else if (node->str[0] == '\'')
		return (SQ);
	else if (node->str[0] == '"')
		return (DQ);
	else if (node->str[0] == '(')
		return (OP);
	else if (node->str[0] == ')')
		return (CP);
	return (rest_of_types(node));
}
