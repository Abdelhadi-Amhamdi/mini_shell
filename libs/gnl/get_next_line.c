/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:48:51 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/24 15:25:57 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_all(char *data, char *buffer)
{
	free(data);
	free(buffer);
	return (NULL);
}

char	*read_file(int fd, char *data)
{
	char	*buffer;
	int		is_nl;
	int		count;

	is_nl = 0;
	count = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!is_nl && count > 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count <= 0 && !data)
			return (free(buffer), NULL);
		else if (count == 0 && data[0] != '\0')
			break ;
		else if (count == -1 && data)
			return (data = free_all(data, buffer));
		buffer[count] = '\0';
		data = ft_join(data, buffer);
		if (ft_search_gnl(data) != -1)
			is_nl = 1;
	}
	return (free(buffer), data);
}

char	*get_line_from_data(const char *data)
{
	char	*line;
	int		nl_index;

	nl_index = ft_search_gnl(data);
	if (nl_index != -1)
	{
		line = malloc(nl_index + 2 * sizeof(char));
		if (!line)
			return (NULL);
		ft_strlcpy(line, data, nl_index + 2);
	}
	else
		line = ft_strdup(data);
	return (line);
}

char	*update_data(const char *data)
{
	char	*new_data;
	int		nl_index;
	int		size;

	nl_index = ft_search_gnl(data);
	if (nl_index != -1)
	{
		size = ft_strlen(data + nl_index + 1);
		new_data = malloc(size + 1 * sizeof(char));
		if (!new_data)
			return (NULL);
		ft_strlcpy(new_data, data + (nl_index + 1), size + 1);
	}
	else
		new_data = NULL;
	free((char *)data);
	return (new_data);
}

char	*get_next_line(int fd)
{
	static char	*data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	data = read_file(fd, data);
	if (!data || !*data)
	{
		if (data)
			free(data);
		return (NULL);
	}
	line = get_line_from_data(data);
	data = update_data(data);
	return (line);
}
