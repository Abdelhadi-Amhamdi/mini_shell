/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:18:54 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/25 14:19:08 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*join_variables(char **before, char **var, char **after, char **str)
{
	char	*temp;

	temp = *var;
	*var = ft_strjoin(*before, *var);
	free(temp);
	temp = *var;
	*var = ft_strjoin(*var, *after);
	free(temp);
	free(*str);
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
	{
		prev->next = new;
		new->prev = prev;
		last->next = next;
		if (next)
			next->prev = last;
	}
}

void	normal_case_handler(char *string, t_lexer **list, t_lexer *tmp,
		t_env *envp)
{
	char	**paths;
	t_lexer	*new;

	paths = all_paths(envp);
	if (contain_spaces(string) && tmp->id != DONT_REMOVESP)
	{
		new = tokenizer(string, paths);
		set_type(&new);
		ft_addup_to_list(new, list, tmp);
		free(string);
	}
	else
		tmp->str = string;
	ft_free(paths);
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
		|| s[*index] == '+')
	{
		len++;
		*index = *index + 1;
	}
	while (s[*index] && s[*index] != 32 && s[*index] != '/' && s[*index] != '.'
		&& s[*index] != '$' && s[*index] != '=' && s[*index] != '-'
		&& s[*index] != '+')
	{
		len++;
		*index = *index + 1;
	}
	return (len);
}
