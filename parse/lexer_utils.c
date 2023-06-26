/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/26 10:12:36 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	add_middle_node(t_lexer *new, t_lexer *prev, t_lexer *next,
		t_lexer *last)
{
	prev->next = new;
	new->prev = prev;
	last->next = next;
	if (next)
		next->prev = last;
}
// void	print_token_list(t_lexer *head)
// {
// 	t_lexer	*cur;

// 	cur = head;
// 	while (cur != NULL)
// 	{
// 		printf("STR : [%s]\n", cur->str);
// 		printf("IS_B: [%u]\n", cur->is_builtin);
// 		printf("IS_O: [%s]\n", cur->is_oper ? "true" : "false");
// 		printf("ID: [%d]\n", cur->id);
// 		if (cur->type == 7)
// 			printf("TYPE: VAR\n");
// 		else
// 			printf("TYPE: [%u]\n", cur->type);
// 		printf("PATH: [%s]\n", cur->path);
// 		cur = cur->next;
// 		printf("------------------------------\n");
// 	}
// }

// void	print_token_list(t_lexer *head)
// {
// 	t_lexer	*cur;

// 	cur = head;
// 	while (cur != NULL)
// 	{
// 		printf("STR : [%s]\n", cur->str);
// 		printf("IS_B: [%u]\n", cur->is_builtin);
// 		printf("IS_O: [%s]\n", cur->is_oper ? "true" : "false");
// 		printf("ID: [%d]\n", cur->id);
// 		if (cur->type == 7)
// 			printf("TYPE: VAR\n");
// 		else
// 			printf("TYPE: [%u]\n", cur->type);
// 		printf("PATH: [%s]\n", cur->path);
// 		cur = cur->next;
// 		printf("------------------------------\n");
// 	}
// }

// void	printTreeHelper(t_tree *root, int depth)
// {
// 	t_lexer	*tmp;

// 	if (root == NULL)
// 		return ;
// 	printTreeHelper(root->right, depth + 1);
// 	for (int i = 0; i < depth; i++)
// 		printf("    ");
// 	printf("%s -- %d -- %d\n", root->str, root->type, root->is_builtin);
// 	if (root->cmd_args)
// 	{
// 		for (int i = 0; i < depth + 1; i++)
// 			printf("    ");
// 		printf("%s ", root->path);
// 		tmp = root->cmd_args;
// 		while (tmp)
// 		{
// 			printf("[{%s} - %d]", tmp->str, tmp->type);
// 			tmp = tmp->next;
// 		}
// 		puts("");
// 	}
// 	printTreeHelper(root->left, depth + 1);
// }

// void	printTree(t_tree *root)
// {
// 	printTreeHelper(root, 0);
// }
