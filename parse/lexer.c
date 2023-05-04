/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:21:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/04 14:33:13 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lexer	*create_token(char *str, int is_token)
{
	t_lexer	*new_token;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
		return (NULL);
	new_token->is_token = is_token;
	new_token->str = ft_strdup(str);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
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

t_lexer	*lexer(char *args)
{
	int		index;
	char	**tabs;
	t_lexer	*list;
	t_lexer	*new_node;

	index = 0;
	list = NULL;
	tabs = args_filter(args);
	while (tabs[index])
	{
		new_node = create_token(tabs[index], is_token(tabs[index][0]));
		if (!new_node)
			return (NULL);
		add_token_to_end(&list, new_node);
		index++;
	}
	ft_free(tabs);
	return (list);
}
