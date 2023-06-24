/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:18:32 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/24 15:53:15 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	get_lenght(char *s, int *index)
{
	int	len;

	len = 0;
	if (s[*index] == '$' && s[*index + 1] == '?')
	{
		*index = *index + 2;
		return (2);
	}
	if (s[*index] == '$' || s[*index] == '/' || s[*index] == '.'
		|| s[*index] == 32 || s[*index] == '-' || s[*index] == '='
		|| s[*index] == '+')
	{
		len++;
		*index = *index + 1;
	}
	while (s[*index] && s[*index] != 32 && s[*index] != '/' && s[*index] != '.'
		&& s[*index] != '$' && s[*index] != '=' && s[*index] != '-'
		&& s[*index] != '+')
	{
		len++;
		*index = *index + 1;
	}
	return (len);
}

char	*get_str_helper(char *var, char *str, int start, char *s)
{
	char	*old;

	old = var;
	if (var[0] == '$' && str)
	{
		var = ft_strdup(str);
		free(old);
	}
	if (!str && s[start] == '$')
	{
		free(old);
		var = NULL;
	}
	return (var);
}

char	*get_string(char *s, int *index, t_env *envp)
{
	char	*var;
	int		start;
	int		len;
	char	*str;

	start = *index;
	len = get_lenght(s, index);
	var = malloc(len + 1);
	if (!var)
		return (ft_putendl_fd("Malloc Failed\n", 2), NULL);
	ft_strlcpy(var, &s[start], len + 1);
	str = ft_get_expand_val(var + 1, envp);
	if (var && !ft_strncmp(var, "$?", 3))
		var = ft_itoa(g_exit_status);
	else if (var && (!var[1] || (var[0] == '$' && !ft_isalpha(var[1]))))
		return (var);
	else
		var = get_str_helper(var, str, start, s);
	free(str);
	return (var);
}

char	*expand(char *var, t_env *envp)
{
	int		i;
	char	*str;
	char	*new;
	char	*old;

	i = 0;
	str = NULL;
	while (var[i])
	{
		old = str;
		new = get_string(var, &i, envp);
		str = ft_strjoin(str, new);
		free(old);
		free(new);
	}
	return (str);
}

//expand variables
void	ft_expand_vars(t_lexer **list, t_env *envp, t_lexer *tmp)
{
	char	*var;

	tmp = *list;
	var = NULL;
	while (tmp)
	{
		if (tmp->type == VAR && tmp->id != DONT_EXPAND)
		{
			expander_helper(list, tmp, var, envp);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
