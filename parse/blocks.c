/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:11:04 by aagouzou          #+#    #+#             */
/*   Updated: 2023/07/12 14:47:30 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	heredoc_to_inrdir(t_parser **list, char *file_name)
{
	t_lexer		*new_node;
	t_parser	*new_item;

	new_node = creat_lexer_node("<");
	new_node->type = RDIR;
	new_node->is_oper = true;
	new_item = create_parser_node(new_node, 1);
	del_node(new_node);
	if (!new_item)
		return ;
	add_node_to_list(list, new_item);
	new_node = creat_lexer_node(file_name);
	new_node->type = HEREDOC_FILE;
	new_item = create_parser_node(new_node, 1);
	del_node(new_node);
	add_node_to_list(list, new_item);
}

t_lexer	*next_arg(t_lexer *arg)
{
	while (arg)
	{
		if (arg->is_oper)
			return (arg);
		arg = arg->next;
	}
	return (arg);
}

t_lexer	*handle_heredoc_case(t_lexer *arg, t_parser **parser_list, t_main *data)
{
	char	*file_name;
	t_lexer	*tmp;

	file_name = NULL;
	if (arg->type == HEREDOC)
	{
		while (arg && arg->type == HEREDOC)
		{
			file_name = start_heredoc(arg, arg->next->is_builtin, data);
			if (!file_name)
			{
				tmp = creat_lexer_node("NONE");
				tmp->id = DEL_HERDOC_NODE;
				return (tmp);
			}
			arg = arg->next->next;
		}
		if (ft_check_next(arg, file_name))
			heredoc_to_inrdir(parser_list, file_name);
		free (file_name);
	}
	return (next_arg(arg));
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
		if (tmp->type == CMD || tmp->type == UNK || tmp->type == VAR)
		{
			tmp = creat_blocks_helper(tmp, &parser_list, data);
			if (tmp && tmp->id == DEL_HERDOC_NODE)
				return (del_node(tmp), _free_parser(&parser_list, 1), NULL);
		}
		else if (tmp->type == HEREDOC)
		{
			if (create_block_doc_helper(tmp, &parser_list, data))
				return (_free_parser(&parser_list, 1), NULL);
			tmp = tmp->next->next;
			while (tmp && (tmp->type == W_SPACE || !(*tmp->str)))
				tmp = tmp->next;
		}
		else
			tmp = add_new_simple_node(tmp, &parser_list);
	}
	return (parser_list);
}
