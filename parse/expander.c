/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/17 11:47:47 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	clean_next_space(t_lexer *tmp)
{
	t_lexer	*cur;
	t_lexer	*space;

	cur = tmp->next->next;
	space = tmp->next;
	tmp->next = cur;
	if (cur)
		cur->prev = tmp;
	del_node(space);
}

void	clean_prev_space(t_lexer *tmp, t_lexer **list)
{
	t_lexer	*cur;
	t_lexer	*space;

	cur = tmp->prev->prev;
	space = tmp->prev;
	if (cur)
	{
		cur->next = tmp;
		tmp->prev = cur;
		del_node(space);
	}
	else
	{
		*list = tmp;
		tmp->prev = NULL;
		del_node(space);
	}
}

void	clean_unsed_spaces(t_lexer **list)
{
	t_lexer	*tmp;

	tmp = *list;
	while (tmp)
	{
		if ((tmp->type == CMD || tmp->type == OP || tmp->type == CP)
			&& tmp->prev && tmp->prev->type == W_SPACE)
		{
			clean_prev_space(tmp, list);
		}
		if ((tmp->type == CMD || tmp->type == OP || tmp->type == CP)
			&& tmp->next && tmp->next->type == W_SPACE)
		{
			clean_next_space(tmp);
		}
		tmp = tmp->next;
	}
}

int	ft_expander(t_lexer *list, t_env *env)
{
	t_lexer	*tmp;
	char	**paths;

	tmp = list;
	paths = all_paths(env);
	ft_expand_vars(&list, env, tmp);
	if (check_qoutes(list) || check_pths(list))
	{
		exit_status = SYNTAX_ERROR_EXIT_STATUS;
		return (ft_free(paths), 1);
	}
	set_type(&list);
	join_args(&list, paths);
	clean_unsed_spaces(&list);
	if (syntax_analyzer(list))
	{
		exit_status = SYNTAX_ERROR_EXIT_STATUS;
		return (ft_free(paths), 1);
	}
	ft_expand_wildcards(&list);
	return (ft_free(paths), 0);
}
