/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 22:41:34 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/17 22:10:42 by aamhamdi         ###   ########.fr       */
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
		return (ft_strdup((char *)s1));
	else if (!s1 && s2)
		return (ft_strdup((char *)s2));
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	p = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (!p)
		return (ft_putendl_fd("Error: Malloc Failed !", 2), NULL);
	ft_memcpy(p, s1, size1);
	ft_memcpy(p + size1, s2, size2);
	p[size1 + size2] = '\0';
	return (p);
}
