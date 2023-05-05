/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:20:38 by aamhamdi          #+#    #+#             */
/*   Updated: 2022/10/23 11:06:46 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if ((count * size) / count != size && count != 0)
		return (0);
	p = malloc(size * count);
	if (!p)
		return (0);
	ft_bzero (p, count * size);
	return (p);
}
