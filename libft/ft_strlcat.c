/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:01:59 by aamhamdi          #+#    #+#             */
/*   Updated: 2022/10/24 17:34:17 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_size ;
	size_t	src_size ;

	i = 0;
	if (!dst && dstsize == 0)
		return (0);
	dest_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dstsize <= dest_size || dstsize == 0)
		return (dstsize + src_size);
	while (src[i] && i < dstsize - dest_size - 1)
	{
		dst[dest_size + i] = src[i];
		i++;
	}
	dst[i + dest_size] = '\0';
	return (src_size + dest_size);
}
