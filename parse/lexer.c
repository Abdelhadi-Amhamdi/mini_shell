/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:21:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/16 11:24:53 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lexer	*create_token(char *str, int is_token, char	**paths)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->is_token = is_token;
	new->str = ft_strdup(str);
	new->path = NULL;
	if(!is_token)
		new->path = get_path(new->str ,paths);
	new->type = check_type(new, new->path);
	new->is_builtin = is_builtin(new->str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

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

void	print_token_list(t_lexer *head)
{
	t_lexer	*current_token;

	current_token = head;
	while (current_token != NULL)
	{
		printf("String: %s\n", current_token->str);
		printf("Is token: %s\n", current_token->is_token ? "true" : "false");
		printf("path	: %s\n",current_token->path);
		printf("is_builtin	: %s\n",current_token->is_builtin ? "true" : "false");
		printf("type : %s\n", (current_token->type == 0) ? "CMD" : ((current_token->type == 1)) ? "UNK": ((current_token->type == 2) ? "TOKEN" : ((current_token->type == 3) ? "ARGS" : ((current_token->type == 4) ? "VAR" : ((current_token->type == 5) ? "FILE" : "Q")))));
		printf("--------\n");
		current_token = current_token->next;
	}
}

void	ft_free(char **tabs)
{
	int	index;

	index = 0;
	while (tabs[index])
	{
		free(tabs[index]);
		index++;
	}
	free(tabs);
}

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

t_lexer	*lexer(char *args, t_env	*env)
{
	char	**paths;
	int		index;
	char	**tabs;
	t_lexer	*list;
	t_lexer	*new_node;

	index = 0;
	list = NULL;
	tabs = args_filter(args);
	paths = all_paths(env);
	while (tabs[index])
	{
		new_node = create_token(tabs[index], is_token(tabs[index][0]), paths);
		if (!new_node)
			return (NULL);
		add_token_to_end(&list, new_node);
		index++;
	}
	ft_free(tabs);
	return (list);
}
