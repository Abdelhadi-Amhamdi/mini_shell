/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:06:58 by aamhamdi          #+#    #+#             */
/*   Updated: 2022/10/25 16:45:20 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	size;

	if (!s)
		return (0);
	if (start >= ft_strlen(s) || !*s || len == 0)
		return (ft_strdup("\0"));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (0);
	ft_strlcpy(p, s + start, len + 1);
	return (p);
}
