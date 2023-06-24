/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:36:41 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/24 11:41:00 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*ft_get_expand_val(char *var, t_env *envp)
{
	while (envp)
	{
		if (!ft_strncmp(var, envp->key, ft_strlen(envp->key) + 1))
			return (ft_strdup(envp->value));
		envp = envp->next;
	}
	return (NULL);
}

char	*extract_before(char *cmd, int *i)
{
	int		start;
	int		len;
	int		index;
	char	*before;

	len = 0;
	start = *i;
	while (cmd[*i] && (cmd[*i] == '\'' || cmd[*i] == '"'))
	{
		*i = *i + 1;
		len++;
	}
	before = malloc(len + 1);
	if (!before)
		return (NULL);
	index = 0;
	while (cmd[start] && (cmd[start] == '\'' || cmd[start] == '"'))
	{
		before[index] = cmd[start];
		index++;
		start++;
	}
	before[index] = '\0';
	return (before);
}

//extract variable to expland
char	*extarct_expand(char *cmd, int *i)
{
	int		start;
	int		len;
	int		index;
	char	*to_expand;

	start = *i;
	len = 0;
	while (cmd[*i] && cmd[*i] != '\'' && cmd[*i] != '"')
	{
		*i = *i + 1;
		len++;
	}
	to_expand = malloc(len + 1);
	if (!to_expand)
		return (NULL);
	index = 0;
	while (cmd[start] && cmd[start] != '\'' && cmd[start] != '"')
	{
		to_expand[index] = cmd[start];
		index++;
		start++;
	}
	to_expand[index] = '\0';
	return (to_expand);
}

//extract after command
char	*extarct_after(char *cmd, int *i)
{
	int		start;
	char	*after;
	int		index;
	int		len;

	index = 0;
	len = 0;
	start = *i;
	while (cmd[*i])
	{
		len++;
		*i = *i + 1;
	}
	after = malloc(len + 1);
	if (!after)
		return (NULL);
	while (cmd[start])
	{
		after[index] = cmd[start];
		index++;
		start++;
	}
	after[index] = '\0';
	return (after);
}
