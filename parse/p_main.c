/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/10 15:27:32 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void ft_free_lexer_list(t_lexer **list)
{
	t_lexer *tmp;
	t_lexer *next;
	tmp = *list;
	if (!tmp)
		return ;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == 8 && tmp->id == -11)
			unlink(tmp->str);
		del_node(tmp);
		tmp = next;
	}
	*list = NULL;
}

void del_p_node(t_parser *node)
{
	if (!node)
		return ;
	node->args_list = NULL;
	free(node->str);
	node->str = NULL;
	if (node->path)
		free(node->path);
	node->path = NULL;
	free(node);
	node = NULL;
}

void ft_free_parser_list(t_parser **list)
{
	t_parser *tmp;
	t_parser *next;

	tmp = *list;
	while (tmp)
	{
		next = tmp->next;
		del_p_node(tmp);
		tmp = next;
	}
	*list = NULL;
}

int ft_tabs_len(char **tabs)
{
	int index;

	index = 0;
	while (tabs[index])
		index++;
	return (index);
}

t_tree *create_node(t_parser *item)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(item->str);
	new_node->type = item->type;
	new_node->is_builtin = item->is_builtin;
	if (item->path)
		new_node->path = ft_strdup(item->path);
	else
		new_node->path  = NULL;
	new_node->cmd_args =  item->args_list;
	new_node->is_op = false;
	new_node->args = NULL;
	new_node->id = item->id;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_tree *create_token_node(t_parser *node, t_tree *left, t_tree *right)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(node->str);
	new_node->type = node->type;
	new_node->cmd_args = NULL;
	new_node->is_op = true;
	new_node->id = node->id;
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
	if (res && !res->left && res->is_op && (res->type == HEREDOC \
	|| res->type == APND || res->type == RDIR) && *list && (*list)->type != CP)
		res->left = term(list);
	return (res);
}

t_tree *factor(t_parser **list)
{
	t_tree	*res;

	res = NULL;
	if ((*list)->type == OP)
	{
		(*list) = (*list)->next;
		res = create_tree(list);
		(*list) = (*list)->next;
	}
	else if ((*list) &&  !(*list)->is_op)
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
    printf("%s -- %d -- %d\n", root->str, root->type, root->id);
	if (root->cmd_args)
	{
		for (int i = 0; i < depth + 1; i++)
			printf("    ");
		printf("%s ", root->path);
		while (root->cmd_args)
		{
			printf("[%s - %d]", root->cmd_args->str, root->cmd_args->type);
			root->cmd_args = root->cmd_args->next;
		}
		puts("");
	}
    printTreeHelper(root->left, depth + 1);
}

void printTree(t_tree *root)
{
    printTreeHelper(root, 0);
}

int	ft_error(char *str)
{
	return (printf("%s `%s'\n", SYNTAX_ERROR_MSG, str));
}

t_tree *formater(char *cmd)
{
	t_parser *tmp;
	t_lexer *lexer_list;
	t_parser *parser_list;
	t_tree *ast_tree;

	lexer_list = NULL;
	parser_list = NULL;
	ast_tree = NULL;
	lexer_list = lexer(cmd, app->env_list);
	if(!lexer_list)
		return (NULL);
	if (ft_expander(lexer_list, app->env_list))
		return (ft_free_lexer_list(&lexer_list), NULL);
	heredoc_handler(&lexer_list);
	parser_list = parser(lexer_list);
	if (!parser_list)
		return (ft_free_lexer_list(&lexer_list), NULL);
	ft_free_lexer_list(&lexer_list);
	tmp = parser_list;
	ast_tree = create_tree(&tmp);
	ft_free_parser_list(&parser_list);
	return (ast_tree);
}
