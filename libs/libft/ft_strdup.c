/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:00:26 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/17 22:09:34 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		tab_size;
	int		i;
	char	*p;

	if (!s1)
		return (NULL);
	tab_size = ft_strlen(s1);
	p = malloc(sizeof(char) * tab_size + 1);
	if (!p)
		return (ft_putendl_fd("Error: Malloc Failed !", 2), NULL);
	i = 0;
	while (i < tab_size)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
