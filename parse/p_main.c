/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/19 18:43:45 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

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

t_tree *create_node(t_parser *item)
{
	t_tree *new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->str = item->str;
	new_node->type = item->type;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_tree *create_token_node(t_parser *node, t_tree *left, t_tree *right)
{
	t_tree *new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->str = node->str;
	new_node->type = node->type;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

t_tree *create_tree(t_parser **list)
{
	t_tree		*res = term(list);
	t_parser	*op;

	while((*list) && (*list)->is_op && (!ft_strncmp((*list)->str , "&&", 2) || !ft_strncmp((*list)->str , "||", 2)))
	{
		op = (*list);
		(*list) = (*list)->next;
		t_tree *right = term(list);
		res = create_token_node(op, res,right);
	}
	return (res);
}

t_tree *term(t_parser **list)
{
	t_tree		*res = factor(list);
	t_parser	*op;

	while((*list) && (*list)->is_op && (ft_strncmp((*list)->str , "&&", 2) && ft_strncmp((*list)->str , "||", 2)))
	{
		op = (*list);
		(*list) = (*list)->next;
		t_tree *right = factor(list);
		res = create_token_node(op, res,right);
	}
	return (res);
}

t_tree *factor(t_parser **list)
{
	t_tree	*res;

	res = NULL;
	if ((*list)&&  !(*list)->is_op)
	{
		res = create_node(*list);
		(*list) = (*list)->next;
	}
	return (res);
}

void printTreeHelper(t_tree *root, int depth)
{
    if (root == NULL) {
        return;
    }
    printTreeHelper(root->right, depth + 1);
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    if (root->type == 'N')
        printf("%s\n", root->str);
    else
        printf("%s\n", root->str);
    printTreeHelper(root->left, depth + 1);
}

void printTree(t_tree *root)
{
    printTreeHelper(root, 0);
}

void	ft_error(char *str)
{
	printf("%s `%s'\n", _ERR_MSG, str);
}

t_parser	*formater(char *cmd, t_env *envp)
{
	t_lexer		*lexer_list;
	t_parser	*parser_list;
	t_tree		*ast_tree;

	ast_tree = NULL;
	lexer_list = lexer(cmd, envp);
	if (ft_expander(lexer_list, envp))
		return (NULL);
	parser_list = parser(lexer_list);
	ft_free_lexer_list(lexer_list);
	if (!parser_list)
		return (NULL);
	ast_tree = create_tree(&parser_list);
	printTree(ast_tree);
	
	return (NULL);
	// return (at_tree);
}
