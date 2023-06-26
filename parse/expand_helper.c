/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:18:54 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/26 09:54:10 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*join_variables(char **before, char **var, char **after)
{
	char	*temp;

	temp = *var;
	*var = ft_strjoin(*before, *var);
	free(temp);
	temp = *var;
	*var = ft_strjoin(*var, *after);
	free(temp);
	return (*var);
}

int	contain_spaces(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (is_space(string[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_addup_to_list(t_lexer *new, t_lexer **list, t_lexer *node)
{
	t_lexer	*last;
	t_lexer	*next;
	t_lexer	*prev;
	t_lexer	*tmp;

	prev = node->prev;
	next = node->next;
	last = get_last_token(new);
	if (!prev)
	{
		*list = new;
		last->next = next;
		if (next)
			next->prev = last;
	}
	else
		add_middle_node(new, prev, next, last);
	tmp = node;
	node = new;
	del_node(tmp);
}

void	normal_case_handler(char *string, t_lexer **list, t_lexer *tmp,
		t_env *envp)
{
	char	**paths;
	t_lexer	*new;
	char	*temp;

	if (contain_spaces(string) && tmp->id != DONT_REMOVESP)
	{
		paths = all_paths(envp);
		temp = string;
		new = tokenizer(string, paths);
		set_type(&new);
		ft_addup_to_list(new, list, tmp);
		free(temp);
		ft_free(paths);
	}
	else
	{
		temp = tmp->str;
		tmp->str = string;
		free(temp);
	}
}

int	get_lenght(char *s, int *index)
{
	int	len;

	len = 0;
	if (s[*index] == '$' && s[*index + 1] == '?')
	{
		*index = *index + 2;
		return (2);
	}
	if (s[*index] == '$' || s[*index] == '/' || s[*index] == '.'
		|| s[*index] == 32 || s[*index] == '-' || s[*index] == '='
		|| s[*index] == '+' || s[*index] == '#')
	{
		len++;
		*index = *index + 1;
	}
	while (s[*index] && s[*index] != 32 && s[*index] != '/' && s[*index] != '.'
		&& s[*index] != '$' && s[*index] != '=' && s[*index] != '-'
		&& s[*index] != '+' && s[*index] != '#')
	{
		len++;
		*index = *index + 1;
	}
	return (len);
}
