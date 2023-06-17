/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:18:32 by aagouzou          #+#    #+#             */
/*   Updated: 2023/06/17 11:11:05 by aagouzou         ###   ########.fr       */
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

int	get_lenght(char *s, int *index)
{
	int	len;

	len = 0;
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

char	*get_string(char *s, int *index, t_env *envp, int last)
{
	char	*old;
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
	if (var && (!var[1] || (var[0] == '$' && !ft_isalpha(var[1]))))
		return (var);
	if (var[0] == '$' && str)
	{
		old = var;
		var = ft_strdup(str);
		free(old);
	}
	else if (!str && last && s[start] == '$')
		var = NULL;
	free(str);
	return (var);
}

char	*expand(char *var, t_env *envp, int last)
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
		new = get_string(var, &i, envp, last);
		str = ft_strjoin(str, new);
		free(old);
		free(new);
	}
	return (str);
}

//expand variables
void	ft_expand_vars(t_lexer **list, t_env *envp, t_lexer *tmp)
{
	char	*before;
	char	*after;

	tmp = *list;
	before = NULL;
	after = NULL;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			expander_helper(tmp, before, after, envp);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
