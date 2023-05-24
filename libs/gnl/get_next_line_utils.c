/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:48:57 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/24 15:29:35 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_search_gnl(const char *data)
{
	int	index;

	index = 0;
	while (data[index])
	{
		if (data[index] == '\n')
			return (index);
		index++;
	}
	return (-1);
}

char	*ft_join(char *data, const char *buffer)
{
	char	*new_data;
	size_t	s1_s;
	size_t	s2_s;

	if (!data)
		data = ft_strdup("");
	s1_s = ft_strlen(data);
	s2_s = ft_strlen(buffer);
	new_data = malloc((s1_s + s2_s + 1) * sizeof(char));
	if (!new_data)
		return (NULL);
	ft_strlcpy(new_data, data, s1_s + 1);
	ft_strlcpy(new_data + s1_s, buffer, s2_s + 1);
	free(data);
	return (new_data);
}
