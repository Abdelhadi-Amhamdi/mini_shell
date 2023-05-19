/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:56 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/19 14:07:14 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*check_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_op_next(str, i))
			return (str);
		if (check_op_prev(str, i))
			return (str);
		i++;
	}
	return (NULL);
}

size_t	count_new_args_size(char *str)
{
	size_t	count;
	int		index;

	count = 0;
	index = 0;
	while (str[index])
	{
		if (check_op_next(str, index))
			count++;
		if (check_op_prev(str, index))
			count++;
		index++;
		count++;
	}
	return (count);
}

char	*filter_args_helper(char *str)
{
	size_t	size;
	char	*new_str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	size = count_new_args_size(str);
	new_str = malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		if (check_op_prev(str, i))
			new_str[j++] = ' ';
		new_str[j++] = str[i];
		if (check_op_next(str, i))
			new_str[j++] = ' ';
	}
	new_str[j] = '\0';
	return (new_str);
}

char	**args_filter(char *str)
{
	char	*args;
	char	**tabs;

	args = NULL;
	args = check_args(str);
	if (args)
		args = filter_args_helper(args);
	else
		args = ft_strdup(str);
	tabs = ft_mini_split(args, ' ');
	free(args);
	if (!tabs)
		return (NULL);
	return (tabs);
}

static size_t	get_tabs_sum(const char *src, char c)
{
	int		i;
	char	current;
	int		quotes;
	size_t	size;

	quotes = 0;
	i = 0;
	size = 0;
	while (src[i])
	{
		if (src[i] == '"' || src[i] == '\'')
		{
			if (!(quotes % 2))
			{
				current = src[i];
				quotes++;
			}
			while (src[++i] && src[i] != current);
			quotes = 0;
			size++;
			if (!src[i])
				return (size);
		}
		else
		{
			if ((src[i] == c && src[i - 1] != c && src[i - 1] \
			!= current && i != 0) || src[i + 1] == '\0')
					size++;	
		}
		i++;
	}
	return (size);
}



static char	**ft_free_all(char **tabs, int index)
{
	while (index >= 0)
	{
		free(tabs[index]);
		index--;
	}
	free(tabs);
	return (0);
}

char	**ft_mini_split(const char *src, char c)
{
	char	**tabs;
	int		i;
	int		len;

	if (!src)
		return (NULL);
	int s = get_tabs_sum(src, c);
	// printf("%d\n", s);
	tabs = (char **)malloc(sizeof(char *) * (s + 1));
	if (!tabs)
		return (NULL);
	i = 0;
	while (*src)
	{
		while (*src && *src == c)
			src++;
		len = 0;
		if (src[len] == '"' || src[len] == '\'')
		{
			char t = src[len];
			while (src[++len] && src[len] != t);
			tabs[i++] = ft_substr(src, 0, ++len);
			if (!src[len - 1])
				break ;
		}
		else
		{
			while (src[len] && src[len] != c)
				len++;
			if (len != 0)
				tabs[i++] = ft_substr(src, 0, len);
		}
		if (len != 0 && !tabs[i - 1])
			return (ft_free_all(tabs, i - 1));
		src += len;
	}
	tabs[i] = NULL;
	return (tabs);
}

void	print_token_list(t_lexer *head)
{
	t_lexer	*cur;

	cur = head;
	while (cur != NULL)
	{
		printf("String: :%s:\n", cur->str);
		// printf("Is token: %s\n", cur->is_oper ? "true" : "false");
		// printf("path	: %s\n",cur->path);
		// printf("is_builtin	: %s\n",cur->is_builtin ? "true" : "false");
		printf("type : %s\n", (cur->type == 0) ? "CMD" : (cur->type == 1) ? "PIPE" \
		 : (cur->type == 2) ? "RDIR" : (cur->type == 3) ? "APND" : (cur->type == 4) ? "AND" : (cur->type == 5) ? "OR" : (cur->type == 6) ? "ARGS" : (cur->type == 7) ? "VAR": (cur->type == 8) ? "FILE": (cur->type == 9) ? "SQ": (cur->type == 10) ? "DQ": (cur->type == 11) ? "OP": ((cur->type == 12) ? "CP": "UNK"));
		// printf("type index %u\n",cur->type);
		printf("-------------------------\n");
		cur = cur->next;
	}
}
