/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:11:04 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/19 15:34:11 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_lexer	*handle_rdir_case(t_parser **parser_list, t_lexer *arg,
		t_lexer **args_list)
{
	if (arg->type != HEREDOC)
	{
		add_node_to_list(parser_list, create_parser_node(arg, 1));
		arg = arg->next;
		add_node_to_list(parser_list, create_parser_node(arg, 1));
		arg = arg->next;
	}
	else
		arg = arg->next->next;
	while (arg && arg->type == W_SPACE)
		arg = arg->next;
	while (arg && !arg->is_oper && arg->type != CP && arg->type != OP)
	{
		add_token_to_end(args_list, ft_nodedup(arg));
		arg = arg->next;
	}
	return (arg);
}

void	heredoc_to_inrdir(t_parser **list, t_lexer *node, char *file_name)
{
	t_lexer		*new_node;
	t_parser	*new_item;

	new_node = ft_nodedup(node->next);
	new_node->str = ft_strdup("<");
	new_node->type = RDIR;
	new_node->is_oper = true;
	new_item = create_parser_node(new_node, 1);
	if (!new_item)
		return ;
	add_node_to_list(list, new_item);
	new_node = ft_nodedup(node);
	new_node->str = ft_strdup(file_name);
	new_node->path = ft_strdup(file_name);
	new_node->type = HEREDOC_FILE;
	new_item = create_parser_node(new_node, 1);
	add_node_to_list(list, new_item);
}

t_lexer	*handle_heredoc_case(t_lexer *arg, t_parser **parser_list, t_main *data)
{
	t_lexer	*tmp;
	char	*file_name;

	if (arg->type == HEREDOC)
	{
		file_name = start_heredoc(arg, arg->next->is_builtin, data);
		if (!file_name)
		{
			tmp = ft_nodedup(arg);
			tmp->id = DEL_HERDOC_NODE;
			return (tmp);
		}
		heredoc_to_inrdir(parser_list, arg, file_name);
		arg = arg->next->next;
	}
	while (arg)
	{
		if (arg->is_oper)
			return (arg);
		arg = arg->next;
	}
	return (arg);
}

t_lexer	*creat_blocks_helper(t_lexer *tmp, t_parser **parser_list, t_main *data)
{
	t_parser	*new_node;
	t_lexer		*ar;
	t_lexer		*args_list;

	args_list = NULL;
	ar = tmp->next;
	new_node = create_parser_node(tmp, tmp->id);
	add_node_to_list(parser_list, new_node);
	if (ar && (ar->type == RDIR || ar->type == APND || ar->type == 16))
	{
		tmp = handle_rdir_case(parser_list, ar, &args_list);
		new_node->args_list = args_list;
		if (ar->type == HEREDOC)
			tmp = handle_heredoc_case(ar, parser_list, data);
	}
	else
		tmp = pass_args_to_cmd(ar, &new_node);
	return (tmp);
}

t_parser	*create_blocks(t_lexer *lexer_list, t_main *data)
{
	t_parser	*parser_list;
	t_lexer		*tmp;

	tmp = lexer_list;
	parser_list = NULL;
	while (tmp)
	{
		if (tmp->type == CMD || tmp->type == UNK)
		{
			tmp = creat_blocks_helper(tmp, &parser_list, data);
			if (tmp && tmp->id == DEL_HERDOC_NODE)
				return (del_node(tmp), NULL);
		}
		else if (tmp->type == HEREDOC)
		{
			if (create_block_doc_helper(tmp, &parser_list, data))
				return (NULL);
			tmp = tmp->next->next;
			while (tmp->type == W_SPACE || !(*tmp->str))
				tmp = tmp->next;
		}
		else
			tmp = add_new_simple_node(tmp, &parser_list);
	}
	return (parser_list);
}
