/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:58:21 by aamhamdi          #+#    #+#             */
/*   Updated: 2022/10/24 17:37:14 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!src && !dest)
		return (0);
	if (dest < src)
		ft_memcpy(dest, src, len);
	else
	{
		while (i < len--)
			((char *)dest)[len] = ((char *)src)[len];
	}	
	return (dest);
}
