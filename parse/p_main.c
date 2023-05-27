/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:52:10 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/27 10:18:14 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void ft_free_lexer_list(t_lexer **list)
{
	t_lexer *tmp;
	t_lexer *next;

	tmp = *list;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*list = NULL;
}

void ft_free_parser_list(t_parser **list)
{
	t_parser *tmp;
	t_parser *next;

	tmp = *list;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*list = NULL;
}

int ft_lst_size(t_lexer *list)
{
	int  size;

	size = 0;
	while (list)
	{
		list = list->next;
		size++;
	}
	return (size);
}

int ft_tabs_len(char **tabs)
{
	int index;

	index = 0;
	while (tabs[index])
		index++;
	return (index);
}

char **get_args(t_parser *node)
{
	char	**cmd_args;
	t_lexer	*tmp;
	int		size;
	int		index;

	index = 0;
	if (node->type != CMD)	
		return (NULL);
	tmp = node->args_list;
	size = ft_lst_size(node->args_list);
	cmd_args = malloc(sizeof(char *) * (size + 2));
	cmd_args[index++] = node->path;
	while (tmp)
	{
		cmd_args[index] = ft_strdup(tmp->str);
		tmp = tmp->next;
		index++;
	}
	cmd_args[index] = NULL;
	return (cmd_args);
}

t_tree *create_node(t_parser *item)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->str = item->str;
	new_node->type = item->type;
	new_node->is_builtin = item->is_builtin;
	new_node->cmd_args =  get_args(item);
	new_node->is_op = false;
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
	new_node->str = node->str;
	new_node->type = node->type;
	new_node->cmd_args = NULL;
	new_node->is_op = true;
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
	if (res->is_op && res->type == HEREDOC)
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
    printf("%s -- %d\n", root->str, root->type);
	int i = 0;
	if (root->cmd_args)
	{
		for (int i = 0; i < depth + 1; i++)
			printf("    ");
		while (root->cmd_args[i])
			printf("%s ", root->cmd_args[i++]);
		puts("");
	}
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

t_tree	*formater(t_app *app)
{
	app->lexer_list = lexer(app->cmd, app->env_list);
	if(!app->lexer_list)
		return (NULL);
	if (ft_expander(app->lexer_list, app->env_list))
		return (NULL);
	app->parser_list = parser(app->lexer_list);
	ft_free_lexer_list(&app->lexer_list);
	if (!app->parser_list)
		return (NULL);
	// print_parser_list(app->parser_list);
	app->ast_tree = create_tree(&app->parser_list);
	ft_free_parser_list(&app->parser_list);
	// return (NULL);
	return (app->ast_tree);
}
