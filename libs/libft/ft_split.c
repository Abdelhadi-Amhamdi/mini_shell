/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:31:59 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/19 14:24:55 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_tabs_sum(const char *src, char c)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (src[i])
	{
		if ((src[i] == c && src[i - 1] != c && i != 0) || src[i + 1] == '\0')
			size++;
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

char	**ft_split(const char *src, char c)
{
	char	**tabs;
	int		i;
	int		len;

	if (!src)
		return (NULL);
	tabs = (char **)malloc(sizeof(char *) * (get_tabs_sum(src, c) + 1));
	if (!tabs)
		return (0);
	i = 0;
	while (*src)
	{
		while (*src && *src == c)
			src++;
		len = 0;
		while (src[len] && src[len] != c)
			len++;
		if (len != 0)
			tabs[i++] = ft_substr(src, 0, len);
		if (len != 0 && !tabs[i - 1])
			return (ft_free_all(tabs, i - 1));
		src += len;
	}
	tabs[i] = 0;
	return (tabs);
}
