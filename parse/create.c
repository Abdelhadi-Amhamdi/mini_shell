/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:15:55 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/23 23:25:26 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	all_inside_is_sp(t_lexer *tmp)
{
	int	i;

	i = 0;
	if (tmp->type == SQ)
	{
		while (tmp->str[i])
		{
			if (tmp->str[i] != '\'' && !is_space(tmp->str[i]))
				return (0);
			i++;
		}
	}
	else if (tmp->type == DQ)
	{
		while (tmp->str[i])
		{
			if (tmp->str[i] != '"' && !is_space(tmp->str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int	contain_only_qs(t_lexer	*tmp)
{
	int	i;

	i = 0;
	if (!(*tmp->str))
		return (1);
	if (tmp->type == SQ)
	{
		while (tmp->str[i])
		{
			if (tmp->str[i] != '\'')
				return (1);
			i++;
		}
	}
	else if (tmp->type == DQ)
	{
		while (tmp->str[i])
		{
			if (tmp->str[i] != '"')
				return (1);
			i++;
		}
	}
	return (0);
}

void	is_printable_sp(t_lexer	*tmp)
{
	if (tmp->type == SQ && all_inside_is_sp(tmp) && contain_only_qs(tmp))
		tmp->id = PREINTABLE_SPACE;
	else if (tmp->type == DQ && all_inside_is_sp(tmp) && contain_only_qs(tmp))
		tmp->id = PREINTABLE_SPACE;
}

void	will_remove_sp(t_lexer *tmp)
{
	if (contain_spaces(tmp->str))
		tmp->id = DONT_REMOVESP;
}

// loop over the list and set types
void	set_type(t_lexer **list)
{
	t_lexer	*tmp;

	tmp = *list;
	while (tmp)
	{
		tmp->type = check_type(tmp, tmp->path);
		is_printable_sp(tmp);
		if (tmp->type == VAR)
			will_remove_sp(tmp);
		tmp = tmp->next;
	}
}

//extract str from line command
char	*extract_str(char *str, int len)
{
	int		i;
	char	*s;

	s = malloc(len + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

//create new token
t_lexer	*create_token(char *str, int len, char **paths)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = extract_str(str, len);
	new->is_oper = is_operator(new->str[0]);
	new->path = NULL;
	if (paths)
		new->path = get_path(new->str, paths);
	new->is_builtin = is_builtin(new->str);
	new->type = -1;
	new->id = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

//add token to end of list
void	add_token_to_end(t_lexer **head, t_lexer *new_token)
{
	t_lexer	*current_token;

	current_token = *head;
	if (!current_token)
		*head = new_token;
	else
	{
		while (current_token->next != NULL)
			current_token = current_token->next;
		current_token->next = new_token;
		new_token->prev = current_token;
	}
}
