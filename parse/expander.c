/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:47:42 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/16 13:30:23 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

// char	*expand(char *var, t_env *envp)
// {
// 	int	index;

// 	index = 0;
// 	while (envp)
// 	{
// 		if (!ft_strncmp(var, envp->key, ft_strlen(envp->key)))// && ft_strlen(envp->key) == ft_strlen(var)
// 			return (envp->value);
// 		envp = envp->next;
// 	}
// 	return (NULL);
// }

// void	ft_expander(t_parser *list, t_env *envp)
// {
// 	t_parser	*tmp;

// 	tmp = list;
// 	while (tmp)
// 	{
// 		if (tmp->type == VAR)
// 			tmp->str = expand(tmp->str+1, envp);
// 		tmp = tmp->next;
// 	}
// }

int check_qoutes(t_lexer *lexer_list)
{
	t_lexer		*tmp;
	int			single_qutes;
	int			double_qutes;
	t_type		current;

	single_qutes = 0;
	double_qutes = 0;
	tmp = lexer_list;
	while (tmp)
	{
		if ((tmp->type == SQ || tmp->type == DQ) \
		&& (!(single_qutes % 2) && !(double_qutes % 2)))
			current = tmp->type;
		if (tmp->type == SQ && tmp->type == current)
			single_qutes++;
		else if (tmp->type == DQ && tmp->type == current)
			double_qutes++;
		tmp = tmp->next;
	}
	if (single_qutes % 2 || double_qutes % 2)
		return (printf("Error Qutes not closed!\n"), 1);
	return (0);
}

t_lexer *ft_expander(t_lexer *list, t_env *env)
{
	// check quotes;
	(void) env;
	if (check_qoutes(list))
		return (NULL);
	// create blocks
	
	// expand vars
	
	// clean list;	
	return (NULL);
}
