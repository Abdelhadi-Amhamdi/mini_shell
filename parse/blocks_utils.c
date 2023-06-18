/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:56:17 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/17 17:02:24 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	ft_check_next(t_lexer *node, char *file_name)
{
	t_lexer	*tmp;

	tmp = node;
	while (tmp && tmp->type == W_SPACE)
		tmp = tmp->next;
	if (tmp && tmp->type == CMD)
		return (0);
	unlink(file_name);
	return (1);
}

t_lexer	*add_new_simple_node(t_lexer *tmp, t_parser **parser_list)
{
	t_parser	*new_node;

	if (tmp->type != W_SPACE)
	{
		new_node = create_parser_node(tmp, tmp->id);
		add_node_to_list(parser_list, new_node);
	}
	tmp = tmp->next;
	return (tmp);
}

t_lexer	*pass_args_to_cmd(t_lexer *ar, t_parser **new_node)
{
	t_lexer		*args_list;

	args_list = NULL;
	while (ar && !ar->is_oper && ar->type != CP && ar->type != OP)
	{
		add_token_to_end(&args_list, ft_nodedup(ar));
		ar = ar->next;
	}
	(*new_node)->args_list = args_list;
	return (ar);
}

int	create_block_doc_helper(t_lexer *tmp, t_parser **parser_list, t_main *data)
{
	char		*file_name;

	file_name = start_heredoc(tmp, tmp->is_builtin, data);
	if (!file_name)
		return (1);
	if (!ft_check_next(tmp->next->next, file_name))
		heredoc_to_inrdir(parser_list, tmp, file_name);
	return (0);
}