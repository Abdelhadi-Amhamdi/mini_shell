/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/24 10:34:04 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_token_list(t_lexer *head)
{
	t_lexer	*cur;

	cur = head;
	while (cur != NULL)
	{
		printf("STR : [%s]\n", cur->str);
		printf("IS_B: [%u]\n", cur->is_builtin);
		printf("IS_O: [%s]\n", cur->is_oper ? "true" : "false");
		printf("ID: [%d]\n", cur->id);
		if (cur->type == 7)
			printf("TYPE: VAR\n");
		else
			printf("TYPE: [%u]\n", cur->type);
		printf("PATH: [%s]\n", cur->path);
		cur = cur->next;
		printf("------------------------------\n");
	}
}

void	printTreeHelper(t_tree *root, int depth)
{
	t_lexer	*tmp;

	if (root == NULL)
		return ;
	printTreeHelper(root->right, depth + 1);
	for (int i = 0; i < depth; i++)
		printf("    ");
	printf("%s -- %d -- %d\n", root->str, root->type, root->is_builtin);
	if (root->cmd_args)
	{
		for (int i = 0; i < depth + 1; i++)
			printf("    ");
		printf("%s ", root->path);
		tmp = root->cmd_args;
		while (tmp)
		{
			printf("[{%s} - %d]", tmp->str, tmp->type);
			tmp = tmp->next;
		}
		puts("");
	}
	printTreeHelper(root->left, depth + 1);
}

void	printTree(t_tree *root)
{
	printTreeHelper(root, 0);
}
