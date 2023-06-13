/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:31 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/13 18:44:19 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_parser	*create_parser_node(t_lexer *l_node, int id)
{
	t_parser	*new_node;

	new_node = malloc(sizeof(t_parser));
	if (!new_node)
		return (NULL);
    new_node->args_list = NULL;
    new_node->is_op = l_node->is_oper;
	new_node->is_builtin = l_node->is_builtin;
    new_node->next = NULL;
    new_node->prev = NULL;
	new_node->id = id;
	new_node->path = ft_strdup(l_node->path);
    new_node->str = ft_strdup(l_node->str);
    new_node->type = l_node->type;
	return (new_node);
}

void	add_node_to_list(t_parser **list, t_parser *item)
{
	t_parser	*tmp;

	tmp = *list;
	if (!*list)
		*list = item;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = item;
		item->prev = tmp;
	}
}

t_lexer *ft_nodedup(t_lexer *node)
{
	t_lexer *new_node;

	new_node =  malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->is_builtin = node->is_builtin;
	// new_node->is_oper = node->is_builtin;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->id = node->id;
	new_node->path = ft_strdup(node->path);
	new_node->str = ft_strdup(node->str);
	new_node->type = node->type;
	return (new_node);
}

t_lexer *handle_rdir_case(t_parser **parser_list, t_lexer *arg, t_lexer **args_list)
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
	while (arg && !arg->is_oper)
	{
		add_token_to_end(args_list, ft_nodedup(arg));
		arg = arg->next;
	}
	return (arg);
}

t_lexer *handle_heredoc_case(t_lexer *arg, t_lexer **args_list, t_main *data)
{
	if (arg->type == HEREDOC)
	{
		t_lexer *tmp;
		char *file_name = start_heredoc(arg, arg->is_builtin, data);
		tmp = ft_nodedup(arg);
		tmp->str = ft_strdup(file_name);
		tmp->path = ft_strdup(file_name);
		tmp->type = HEREDOC_FILE;
		arg = arg->next->next;
		while (arg && arg->type == W_SPACE)
			arg = arg->next;
		if (!arg ||( arg &&  (arg->is_oper || arg->type == ARGS)))
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
			return arg;
		arg = arg->next;
	}
	return (arg);
}

int ft_check_next(t_lexer *node)
{
	t_lexer *tmp;

	tmp = node;
	while (tmp && tmp->type == W_SPACE)
		tmp = tmp->next;
	if (tmp && tmp->type == CMD)
		return (0);
	return (1);
}

t_parser *create_blocks(t_lexer *lexer_list, t_main *data)
{
	t_parser *parser_list;
	t_lexer *args_list;
	t_lexer *tmp;
	t_lexer *first_arg;
	t_parser *new_node;
	
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
			if (first_arg && (first_arg->type == RDIR || first_arg->type == APND || first_arg->type == HEREDOC))
			{
				tmp = handle_rdir_case(&parser_list, first_arg, &args_list);
				new_node->args_list = args_list;				
				if (first_arg->type == HEREDOC)
					tmp = handle_heredoc_case(first_arg, &new_node->args_list, data);
			}
			else
			{
				while (first_arg && !first_arg->is_oper && first_arg->type != CP && first_arg->type != OP)
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
			t_lexer *tmp1;
			char *file_name;
			
			file_name = start_heredoc(tmp, tmp->is_builtin, data);
			if (!file_name)
				return (NULL);
			if ((tmp->prev && tmp->prev->type == CMD) || !ft_check_next(tmp->next->next))
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

t_parser	*parser(t_lexer *lexer_list, t_main *data)
{
	t_parser	*parser_list;

	parser_list = create_blocks(lexer_list, data);
	if (!parser_list)
		return (NULL);
	return (parser_list);
}
