/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 22:41:34 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/13 13:34:50 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	size1;
	size_t	size2;

	if (!s1 && !s2)
		return (0);
	else if (s1 && !s2)
		return((char*)s1);
	else if (!s1 && s2)
		return((char*)s2);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	p = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (!p)
		return (0);
	ft_memcpy(p, s1, size1);
	ft_memcpy(p + size1, s2, size2);
	// free((void	*)s1);
	// free((void	*)s2);
	p[size1 + size2] = '\0';
	return (p);
}
