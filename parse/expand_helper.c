/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:18:54 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/21 13:06:11 by aagouzou         ###   ########.fr       */
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

// t_lexer	*find_node(t_list **list, t_lexer *node)
// {
// 	t_lexer	*cur;

// 	cur = *list;
// 	while (cur)
// 	{
// 		if (cur == node)
// 	}
// }

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
		if(next)
			next->prev = last;
	}
}

void	expander_helper(t_lexer **list, t_lexer *tmp, char *before, char *after, t_env *envp)
{
	int		i;
	char	*temp;
	char	*var;
	char	*string;
	t_lexer	*new;

	i = 0;
	before = extract_before(tmp->str, &i);
	var = extarct_expand(tmp->str, &i);
	after = extarct_after(tmp->str, &i);
	temp = var;
	var = expand(var, envp, 1);
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
		if (contain_spaces(string) && tmp->id != DONT_REMOVESP)
		{
			new = tokenizer(string, all_paths(envp));
			set_type(&new);
			ft_addup_to_list(new, list, tmp);
		}
		else
			tmp->str = string;
	}
	free(before);
	free(after);
}

//extarct before command
char	*extract_before(char *cmd, int *i)
{
	int		start;
	int		len;
	int		index;
	char	*before;

	len = 0;
	start = *i;
	while (cmd[*i] && (cmd[*i] == '\'' || cmd[*i] == '"'))
	{
		*i = *i + 1;
		len++;
	}
	before = malloc(len + 1);
	if (!before)
		return (NULL);
	index = 0;
	while (cmd[start] && (cmd[start] == '\'' || cmd[start] == '"'))
	{
		before[index] = cmd[start];
		index++;
		start++;
	}
	before[index] = '\0';
	return (before);
}

//extract variable to expland
char	*extarct_expand(char *cmd, int *i)
{
	int		start;
	int		len;
	int		index;
	char	*to_expand;

	start = *i;
	len = 0;
	while (cmd[*i] && cmd[*i] != '\'' && cmd[*i] != '"')
	{
		*i = *i + 1;
		len++;
	}
	to_expand = malloc(len + 1);
	if (!to_expand)
		return (NULL);
	index = 0;
	while (cmd[start] && cmd[start] != '\'' && cmd[start] != '"')
	{
		to_expand[index] = cmd[start];
		index++;
		start++;
	}
	to_expand[index] = '\0';
	return (to_expand);
}

//extract after command
char	*extarct_after(char *cmd, int *i)
{
	int		start;
	char	*after;
	int		index;
	int		len;

	index = 0;
	len = 0;
	start = *i;
	while (cmd[*i])
	{
		len++;
		*i = *i + 1;
	}
	after = malloc(len + 1);
	if (!after)
		return (NULL);
	while (cmd[start])
	{
		after[index] = cmd[start];
		index++;
		start++;
	}
	after[index] = '\0';
	return (after);
}
