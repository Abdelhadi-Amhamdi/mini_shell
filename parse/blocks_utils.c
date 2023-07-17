/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:56:17 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/17 14:47:19 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_lexer	*handle_rdir_case(t_parser **parser_list, t_lexer *arg,
		t_lexer **args_list)
{
	t_lexer	*tmp;

	while (arg && (arg->type == RDIR || arg->type == APND))
	{
		add_node_to_list(parser_list, create_parser_node(arg, 1));
		arg = arg->next;
		add_node_to_list(parser_list, create_parser_node(arg, 1));
		arg = arg->next;
	}
	if (arg && arg->type == HEREDOC)
		arg = arg->next->next;
	while (arg && arg->type == W_SPACE && arg->id != PREINTABLE_SPACE)
		arg = arg->next;
	while (arg && !arg->is_oper && arg->type != CP && arg->type != OP)
	{
		tmp = ft_nodedup(arg);
		add_token_to_end(args_list, tmp);
		arg = arg->next;
	}
	return (arg);
}

int	ft_check_next(t_lexer *node, char *file_name)
{
	t_lexer	*tmp;

	tmp = node;
	while (tmp && tmp->type == W_SPACE)
		tmp = tmp->next;
	if (tmp && (tmp->type == CMD \
	|| tmp->type == UNK))
	{
		unlink(file_name);
		return (0);
	}
	return (1);
}

t_lexer	*add_new_simple_node(t_lexer *tmp, t_parser **parser_list)
{
	t_parser	*new_node;

	new_node = create_parser_node(tmp, tmp->id);
	add_node_to_list(parser_list, new_node);
	tmp = tmp->next;
	return (tmp);
}

t_lexer	*pass_args_to_cmd(t_lexer *ar, t_parser **new_node)
{
	t_lexer		*args_list;

	args_list = NULL;
	while (ar && ar->type == W_SPACE && ar->id != PREINTABLE_SPACE)
		ar = ar->next;
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

	file_name = start_heredoc(tmp, tmp->next->is_builtin, data);
	if (!file_name)
		return (1);
	heredoc_to_inrdir(parser_list, file_name);
	free (file_name);
	return (0);
}
