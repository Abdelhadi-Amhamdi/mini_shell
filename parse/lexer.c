/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:21:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/18 10:36:18 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_token_list(t_lexer *head)
{
	t_lexer	*cur;

	cur = head;
	while (cur != NULL)
	{
		printf("String: %s\n", cur->str);
		printf("Is token: %s\n", cur->is_oper ? "true" : "false");
		printf("path	: %s\n",cur->path);
		printf("is_builtin	: %s\n",cur->is_builtin ? "true" : "false");
		printf("type : %s\n", (cur->type == 0) ? "CMD" : (cur->type == 1) ? "PIPE" \
		 : (cur->type == 2) ? "RDIR" : (cur->type == 3) ? "APND" : (cur->type == 4) ? "AND" : (cur->type == 5) ? "OR" : (cur->type == 6) ? "ARGS" : (cur->type == 7) ? "VAR": (cur->type == 8) ? "FILE": (cur->type == 9) ? "SQ": (cur->type == 10) ? "DQ": (cur->type == 11) ? "OP": ((cur->type == 12) ? "CP": "UNK"));
		printf("type index %u\n",cur->type);
		printf("-------------------------\n");
		cur = cur->next;
	}
}

t_lexer	*create_token(char *str, int is_token, char	**paths)
{
	t_lexer	*new;
	(void)paths;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->is_oper = is_token;
	new->str = ft_strdup(str);
	new->path = NULL;
	// if two command (error)
	// if(!is_token) 
	// 	new->path = get_path(new->str ,paths);
	// new->type = check_type(new, new->path);
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
	t_lexer	*node;
	// int	abslt;

	index = 0;
	list = NULL;
	tabs = args_filter(args);
	if (!tabs)
		return (NULL);
	paths = all_paths(env);
	while (tabs[index])
	{
		// abslt = is_absolute_path(tabs[index]);
		node = create_token(tabs[index], is_special_oper(tabs[index][0]), paths);
		if (!node)
			return (NULL);
		if(!node->is_oper || !node->prev || node->prev->type != 0)
			node->path = get_path(node->str ,paths);
		node->type = check_type(node, node->path);
		add_token_to_end(&list, node);
		index++;
	}
	ft_free(tabs);
	return (list);
}
