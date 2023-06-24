/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:18:54 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/24 11:39:23 by aagouzou         ###   ########.fr       */
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

void	expander_helper(t_lexer **list, t_lexer *tmp, char *var,
		t_env *envp)
{
	int		i;
	char	*temp;
	char	*before;
	char	*after;
	char	*string;

	i = 0;
	before = extract_before(tmp->str, &i);
	var = extarct_expand(tmp->str, &i);
	after = extarct_after(tmp->str, &i);
	temp = var;
	var = expand(var, envp);
	free(temp);
	if (!var)
	{
		temp = tmp->str;
		tmp->str = var;
		free(temp);
	}
	else
	{
		string = join_variables(&before, &var, &after, &(tmp->str));
		normal_case_handler(string, list, tmp, envp);
	}
	free(before);
	free(after);
}

//extarct before command
