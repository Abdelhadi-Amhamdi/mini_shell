/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:58:49 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/17 21:50:58 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*ft_strjoin_entrys(char const *s1, char const *s2)
{
	char	*p;
	size_t	size1;
	size_t	size2;

	if (!s1 || !s2)
		return (0);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	p = (char *)malloc((size1 + size2 + 2) * sizeof(char));
	if (!p)
		return (0);
	ft_memcpy(p, s1, size1);
	ft_memcpy(p + size1, s2, size2);
	p[size1 + size2] = ' ';
	p[size1 + size2 + 1] = '\0';
	free((char *)s1);
	return (p);
}

int	check_end(t_wildcard_data data, char *cnd)
{
	while (data.cnd_index < (int)ft_strlen(cnd))
	{
		if (cnd[data.cnd_index++] != '*')
			return (0);
	}
	return (1);
}

int	is_match(char *str, char *cnd)
{
	t_wildcard_data	data;

	data = init_data();
	while (str[data.str_index])
	{
		if (cnd[data.cnd_index] == str[data.str_index])
		{
			data.str_index++;
			data.cnd_index++;
		}
		else if (cnd[data.cnd_index] == '*')
		{
			data.next_card = ++data.cnd_index;
			data.backtrack = data.str_index;
		}
		else if (data.next_card == -1)
			return (0);
		else
		{
			data.cnd_index = data.next_card;
			data.str_index = ++data.backtrack;
		}
	}
	return (check_end(data, cnd));
}

int	allow_hidden(char *file_name, char *cnd)
{
	if ((cnd[0] == '.' && file_name[0] == '.') || file_name[0] != '.')
		return (1);
	return (0);
}

char	*wildcard(char *condition)
{
	DIR				*dir;
	char			*data;
	struct dirent	*entry;

	dir = opendir("./");
	if (dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	data = ft_calloc(1, 1);
	if (!data)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (is_match(entry->d_name, condition) && \
		allow_hidden(entry->d_name, condition))
			data = ft_strjoin_entrys(data, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (data);
}
