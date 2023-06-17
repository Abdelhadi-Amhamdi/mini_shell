/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:37:49 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/16 14:38:56 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

//handle spaces case
char	*ft_spaces(t_lexer **list, char *cmd, char **paths)
{
	t_lexer	*new;
	int		i;

	i = 0;
	while (cmd[i] && is_space(cmd[i]))
		i++;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}

//handle oneoperator case
char	*ft_oneoperator(t_lexer **list, char *cmd, char c, char **paths)
{
	int		i;
	t_lexer	*new;

	if (*(cmd + 1) == c)
		i = 2;
	else
		i = 1;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}

//handle parenthesses case
char	*ft_parentheses(t_lexer **list, char *cmd, char **paths)
{
	t_lexer	*new;
	int		i;

	i = 1;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}

//handle quotes case
char	*ft_quotes(t_lexer **list, char *cmd, char c, char **paths)
{
	t_lexer	*new;
	int		i;

	i = 1;
	while (cmd[i] && cmd[i] != c)
		i++;
	i++;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}

//handle variable case
char	*ft_variable(t_lexer **list, char *cmd, char **paths)
{
	t_lexer	*new;
	int		i;

	i = 1;
	while (cmd[i] && !is_space(cmd[i]) && cmd[i] != '&' && cmd[i] != '|')
		i++;
	new = create_token(cmd, i, paths);
	add_token_to_end(list, new);
	return (&cmd[i]);
}
