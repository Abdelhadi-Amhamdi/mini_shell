/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/15 15:45:16 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"



t_tree *term();
t_tree *factor();


void	ft_free_lexer_list(t_lexer *list)
{
	t_lexer	*tmp;
	t_lexer	*next;

	tmp = list;
	while (tmp)
	{
		next = tmp->next;
		free (tmp);
		tmp = next;
	}
}

// typedef struct s_tree 
// {
// 	char				*str;
// 	t_type			type;
// 	char				*path;
// 	t_boolean		is_builtin;
// 	struct s_tree	*left;
// 	struct s_tree	*right;
// } t_tree;

// t_tree *creat_node(t_parser *item)
// {
// 	t_tree *new_node;

// 	new_node = malloc(sizeof(t_tree));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->str = node->str;
// 	new_node->type = node->type;

// 	new_node->str = item->str;
// 	new_node->type = item->type;
// 	new_node->path = item->path;
// 	new_node->is_builtin = item->is_builtin;
// 	new_node->left = NULL;
// 	new_node->right = NULL;
// 	return (new_node);
// }

// t_tree *create_token_node(t_parser *node, t_tree *left, t_tree *right)
// {
// 	t_tree *new_node;

// 	new_node = malloc(sizeof(t_tree));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->str = node->str;
// 	new_node->type = node->type;
// 	new_node->left = left;
// 	new_node->right = right;
// 	return (new_node);
// }

// t_tree *create_tree()
// {
// 	t_tree *res = term();
// 	t_parser *tmp;

// 	while(parser_list && parser_list->type == TOKEN && \
// 	(!ft_strncmp(parser_list->str , "&&", 2) || !ft_strncmp(parser_list->str , "||", 2)))
// 	{
// 		tmp = parser_list;
// 		parser_list = parser_list->next;
// 		t_tree *right = term();
// 		res = create_token_node(tmp, res,right);
// 	}
// 	return (res);
// }

// t_tree *term()
// {
// 	t_tree *res = factor();
// 	t_parser *tmp;

// 	while(parser_list && parser_list->type == TOKEN && \
// 	(ft_strncmp(parser_list->str , "&&", 2) && ft_strncmp(parser_list->str , "||", 2)))
// 	{
// 		tmp = parser_list;
// 		parser_list = parser_list->next;
// 		t_tree *right = factor();
// 		res = create_token_node(tmp, res,right);
// 	}
// 	return (res);
// }

// t_tree *factor()
// {
// 	t_tree *res;

// 	res = NULL;
// 	if (parser_list &&  parser_list->type != TOKEN)
// 	{
// 		res = create_node(parser_list);
// 		parser_list = parser_list->next;
// 	}
// 	return (res);
// }

// void printTreeHelper(t_tree *root, int depth) {
//     if (root == NULL) {
//         return;
//     }
//     printTreeHelper(root->right, depth + 1);
//     for (int i = 0; i < depth; i++) {
//         printf("    ");
//     }
//     if (root->type == 'N')
//         printf("%s\n", root->str);
//     else
//         printf("%s\n", root->str);
//     printTreeHelper(root->left, depth + 1);
// }

// void printTree(t_tree *root) {
//     printTreeHelper(root, 0);
// }

t_parser	*formater(char *cmd, t_env *envp)
{
	t_lexer		*lexer_list;
	// t_tree		*AST;
	t_parser	*parser_list;
	// t_tree		*my_tree;

	lexer_list = lexer(cmd);
	// AST = NULL;
	// print_token_list(lexer_list);
	parser_list = parser(lexer_list, envp);
	print_parser_list(parser_list);
	ft_free_lexer_list(lexer_list);
	// AST = create_tree();
	// printTree(AST);
	ft_expander(parser_list, envp);
	return (parser_list);
	// return (NULL);
	
	// ft_expander(parser_list, envp);
	// my_tree = create_tree(parser_list);
	
	// return (parser_list);
}
