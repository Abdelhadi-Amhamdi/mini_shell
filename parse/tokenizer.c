/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:27:16 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/26 08:43:33 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

//check is space
int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

//handle normal case
char	*ft_word(t_lexer **list, char *cmd, char **paths)
{
	int		i;
	t_lexer	*new;

	i = 0;
	while (cmd[i] && !is_operator(cmd[i]) && cmd[i] != '\'' && cmd[i] != '"'
		&& cmd[i] != '$' && !is_space(cmd[i]) && cmd[i] != '(' && cmd[i] != ')')
		i++;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}

//split cmd into tokens
t_lexer	*tokenizer(char *cmd, char **paths)
{
	t_lexer	*list;

	list = NULL;
	while (cmd && *cmd && is_space(*cmd))
		cmd++;
	while (cmd && *cmd != '\0')
	{
		if (is_space(*cmd))
			cmd = ft_spaces(&list, cmd, paths);
		else if (*cmd == '|')
			cmd = ft_oneoperator(&list, cmd, *cmd, paths);
		else if (*cmd == '&')
			cmd = ft_oneoperator(&list, cmd, *cmd, paths);
		else if (*cmd == '(' || *cmd == ')')
			cmd = ft_parentheses(&list, cmd, paths);
		else if (*cmd == '\'' || *cmd == '"')
			cmd = ft_quotes(&list, cmd, *cmd, paths);
		else if (*cmd == '>' || *cmd == '<')
			cmd = ft_oneoperator(&list, cmd, *cmd, paths);
		else if (*cmd == '$')
			cmd = ft_variable(&list, cmd, paths);
		else
			cmd = ft_word(&list, cmd, paths);
	}
	return (list);
}
