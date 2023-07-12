/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:33:29 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/12 14:53:24 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_tree	*factor(t_parser **list)
{
	t_tree	*res;

	res = NULL;
	if ((*list)->type == OP)
	{
		(*list) = (*list)->next;
		res = create_tree(list);
		(*list) = (*list)->next;
	}
	else if ((*list) && !(*list)->is_op)
	{
		res = create_node(*list);
		(*list) = (*list)->next;
	}
	return (res);
}

void	print_tree_helper(t_tree *ast, int depth)
{
	t_lexer	*tmp;

	if (!ast)
		return ;
	print_tree_helper(ast->right , depth + 3);
	for (int i = 0; i <= depth; i++)
		printf(" ");
	printf("[%s]", ast->str);
	if (ast->cmd_args)
	{
		tmp = ast->cmd_args;
		while (tmp)
		{
			if (tmp->type != W_SPACE)
				printf("    {%s}", tmp->str);
			tmp = tmp->next;
		}
	}
	puts("");
	print_tree_helper(ast->left, depth + 3);
}

void	printTree(t_tree *root)
{
	if (root)
		print_tree_helper(root, 0);
}
