/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:11:04 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/16 18:25:25 by aagouzou         ###   ########.fr       */
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
	while (arg && !arg->is_oper && arg->type != CP && arg->type != OP)
	{
		add_token_to_end(args_list, ft_nodedup(arg));
		arg = arg->next;
	}
	return (arg);
}

t_lexer	*handle_heredoc_case(t_lexer *arg, t_lexer **args_list, t_main *data)
{
	t_lexer	*tmp;
	char	*file_name;

	if (arg->type == HEREDOC)
	{
		file_name = start_heredoc(arg, arg->is_builtin, data);
		if (!file_name)
		{
			tmp = ft_nodedup(arg);
			tmp->id = -11;
			return (tmp);
		}
		tmp = ft_nodedup(arg);
		tmp->str = ft_strdup(file_name);
		tmp->path = ft_strdup(file_name);
		tmp->type = HEREDOC_FILE;
		arg = arg->next->next;
		while (arg && arg->type == W_SPACE)
			arg = arg->next;
		if (!arg || (arg && (arg->is_oper || arg->type == ARGS)))
			add_token_to_end(args_list, tmp);
		else
		{
			unlink(tmp->str);
			del_node(tmp);
		}
	}
	while (arg)
	{
		if (arg->is_oper)
			return (arg);
		arg = arg->next;
	}
	return (arg);
}

int	ft_check_next(t_lexer *node)
{
	t_lexer	*tmp;

	tmp = node;
	while (tmp && tmp->type == W_SPACE)
		tmp = tmp->next;
	if (tmp && tmp->type == CMD)
		return (0);
	return (1);
}

t_parser	*create_blocks(t_lexer *lexer_list, t_main *data)
{
	t_parser	*parser_list;
	t_lexer		*args_list;
	t_lexer		*tmp;
	t_lexer		*first_arg;
	t_parser	*new_node;
	t_lexer		*tmp1;
	char		*file_name;

	tmp = lexer_list;
	parser_list = NULL;
	while (tmp)
	{
		if (tmp->type == CMD || tmp->type == UNK)
		{
			new_node = create_parser_node(tmp, tmp->id);
			add_node_to_list(&parser_list, new_node);
			first_arg = tmp->next;
			args_list = NULL;
			if (first_arg && (first_arg->type == RDIR || first_arg->type == APND
					|| first_arg->type == HEREDOC))
			{
				tmp = handle_rdir_case(&parser_list, first_arg, &args_list);
				new_node->args_list = args_list;
				if (first_arg->type == HEREDOC)
				{
					tmp = handle_heredoc_case(first_arg, &new_node->args_list,
							data);
					if (tmp && tmp->id == -11)
					{
						del_node(tmp);
						return (NULL);
					}
				}
			}
			else
			{
				while (first_arg && !first_arg->is_oper && first_arg->type != CP
					&& first_arg->type != OP)
				{
					add_token_to_end(&args_list, ft_nodedup(first_arg));
					first_arg = first_arg->next;
				}
				new_node->args_list = args_list;
				tmp = first_arg;
			}
		}
		else if (tmp->type == HEREDOC)
		{
			file_name = start_heredoc(tmp, tmp->is_builtin, data);
			if (!file_name)
				return (NULL);
			if (!ft_check_next(tmp->next->next))
			{
				tmp1 = ft_nodedup(tmp->next);
				tmp1->str = ft_strdup("<");
				tmp1->type = RDIR;
				tmp1->is_oper = true;
				add_node_to_list(&parser_list, create_parser_node(tmp1, 1));
				tmp1 = ft_nodedup(tmp);
				tmp1->str = ft_strdup(file_name);
				tmp1->path = ft_strdup(file_name);
				tmp1->type = HEREDOC_FILE;
				add_node_to_list(&parser_list, create_parser_node(tmp1, 1));
			}
			else
				unlink(file_name);
			tmp = tmp->next->next;
			while (tmp && tmp->type == W_SPACE)
				tmp = tmp->next;
		}
		else
		{
			new_node = create_parser_node(tmp, tmp->id);
			add_node_to_list(&parser_list, new_node);
			new_node->args_list = NULL;
			tmp = tmp->next;
		}
	}
	return (parser_list);
}
