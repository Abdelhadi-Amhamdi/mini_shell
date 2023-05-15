/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/12 14:30:36 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"


typedef struct s_tree 
{
	char				*str;
	t_type			type;
	char				*path;
	t_boolean		is_builtin;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;

t_tree *creat_node(t_parser *item)
{
	t_tree *new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->str = item->str;
	new_node->type = item->type;
	new_node->path = item->path;
	new_node->is_builtin = item->is_builtin;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void add_to_tree(t_tree **root, t_tree *node)
{
	if (!(*root))
		*root = *node;
	else
	{
		
	}
	
}

t_parser *get_next_token(t_parser *list)
{
	if (!list)
		return (NULL);
	while (list)
	{
		if (list->type == TOKEN)
			return (list);
		list = list->prev;
	}
	return (NULL);
}

t_tree *create_tree(t_parser *list)
{
	t_tree *root;
	t_parser *tmp;

	root = NULL;
	while(list)
	{
		if (list->type == TOKEN && \
		(!ft_strncmp(list->str, "&&", 2) || !ft_strncmp(list->str, "||", 2)))
		{
			add_to_tree(&root, creat_node(list));
			break ;
		}
		list = list->next;
	}
	tmp = list;
	while (list)
	{
		t_parser *token = get_next_token(list->prev);
		if (token)
		{
			
		}
		list = list->prev;
	}
	
}

t_parser	*formater(char *cmd, t_env *envp)
{
	t_lexer		*lexer_list;
	t_parser	*parser_list;
	t_tree		*my_tree;

	lexer_list = lexer(cmd);
	// print_token_list(lexer_list);
	parser_list = parser(lexer_list, envp);
	// print_parser_list(parser_list);
	
	ft_expander(parser_list, envp);
	my_tree = create_tree(parser_list);
	
	return (parser_list);
}
