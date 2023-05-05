/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:14:33 by aamhamdi          #+#    #+#             */
/*   Updated: 2022/10/26 11:22:09 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	m_trim(const char *s, const char *set, int index, char type)
{
	int	i;
	int	n;

	i = index;
	while (s[i])
	{
		n = 0;
		while (set[n])
		{
			if (s[i] == set[n])
			{
				if (type == 'i')
					i++;
				else if (type == 'd')
					i--;
				break ;
			}
			n++;
		}
		if (set[n] == '\0')
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		index;
	int		first_char;
	int		last_char;
	int		size;

	if (!s1 || !set)
		return (0);
	index = 0;
	size = (int)ft_strlen(s1);
	first_char = m_trim(s1, set, index, 'i');
	if (first_char == size)
		return (ft_strdup("\0"));
	last_char = m_trim(s1, set, size - 1, 'd');
	return (ft_substr(s1, first_char, (last_char - first_char + 1)));
}
