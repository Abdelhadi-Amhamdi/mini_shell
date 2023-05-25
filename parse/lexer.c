/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:21:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/25 21:55:58 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lexer	*create_token(char *str, int is_token, char	**paths)
{
	t_lexer	*new;
	(void)paths;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->is_oper = is_token;
	new->str = ft_strdup(str);
	new->path = NULL;
	new->is_builtin = is_builtin(new->str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_token_to_end(t_lexer **head, t_lexer *new_token)
{
	t_lexer	*current_token;

	current_token = *head;
	if (!current_token)
		*head = new_token;
	else
	{
		while (current_token->next != NULL)
			current_token = current_token->next;
		current_token->next = new_token;
		new_token->prev = current_token;
	}
}

void	ft_free(char **tabs)
{
	int	index;

	index = 0;
	while (tabs[index])
	{
		free(tabs[index]);
		index++;
	}
	free(tabs);
}

char	**all_paths(t_env *env)
{
	char	*path;

	path = NULL;
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 4))
			path = env->value;
		env = env->next;
	}
	if (path)
		return (ft_split(path, ':'));
	return (NULL);
}


void	_ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

int is_absolute(char *str)
{
	while(*str)
	{
		if(*str == '/')
			return (1);
		str++;
	}
	return (0);
}

char *extract_cmd(char *cmd)
{
	char *new;
	int len;

	while(*cmd)
		cmd++;
	cmd--;
	len = 0;
	while (*cmd && *cmd != '/')
	{
		cmd--;
		len++;
	}
	cmd++;
	new = malloc ((len * sizeof(char )) + 1);
	if(!new)
		ft_error("Error in malloc");
	len = 0;
	while(*cmd)
	{
		new[len] = *cmd;
		cmd++;
		len++;
	}
	cmd[len] = '\0';
	return(new);
}

int validate_cmd(char *cmd)
{
	if(!access(cmd,F_OK | X_OK))
		return(0);
	return(1);
}

t_lexer	*lexer(char *args, t_env	*env)
{
	char	**paths;
	int		index;
	char	**tabs;
	t_lexer	*list;
	t_lexer	*node;

	index = 0;
	list = NULL;
	tabs = args_filter(args);
	if (!tabs)
		return (NULL);
	paths = all_paths(env);
	while (tabs[index])
	{
		
		node = create_token(tabs[index], is_operator(tabs[index][0]), paths);
		if (!node)
			return (NULL);
		if (!node->is_oper && !node->path)
			node->path = get_path(node->str ,paths);
		add_token_to_end(&list, node);
		// node = last_node(list);
		node = get_last_token(list);
		node->type = check_type(node, node->path);
		if((is_absolute(node->str) && !node->prev) || (is_absolute(node->str) && node->prev->type == PIPE))
		{
				if(validate_cmd(node->str))
					return (ft_putendl_fd("command not found",2), NULL);
				node->path = node->str;
				node->str = extract_cmd(node->str);
				node->type = CMD;
		}
		index++;
	}
	// print_token_list(list);
	ft_free(tabs);
	ft_free(paths);
	return (list);
}
