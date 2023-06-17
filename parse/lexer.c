/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:21:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/16 15:38:30 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//get all paths
char	**all_paths(t_env *env)
{
	char	*path;

	path = NULL;
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 4))
			path = env->value;
		env = env->next;
	}
	if (path)
		return (ft_split(path, ':'));
	return (NULL);
}

void	set_tokens_ids(t_lexer **list)
{
	t_lexer	*tmp;
	int		index;

	tmp = *list;
	index = 0;
	while (tmp)
	{
		tmp->id = index;
		index++;
		tmp = tmp->next;
	}
}

void	will_expand(t_lexer **list)
{
	t_lexer	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == HEREDOC && tmp->next && (tmp->next->str[0] == '\''
				|| tmp->next->str[0] == '"'))
			tmp->next->is_builtin = true;
		tmp = tmp->next;
	}
}

// main lexer function
t_lexer	*lexer(char *cmd, t_env *env)
{
	char	**paths;
	t_lexer	*list;

	paths = all_paths(env);
	list = tokenizer(cmd, paths);
	set_type(&list);
	clean_spaces(&list);
	set_tokens_ids(&list);
	will_expand(&list);
	ft_free(paths);
	return (list);
}
