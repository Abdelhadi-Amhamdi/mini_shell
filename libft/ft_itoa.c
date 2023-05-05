/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:25:21 by aamhamdi          #+#    #+#             */
/*   Updated: 2022/10/22 11:41:25 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_calc(int c)
{
	int	size;

	size = 0;
	if (c < 0)
		size += 1;
	while (c && ++size)
		c = c / 10;
	return (size);
}

char	*ft_itoa(int nb)
{
	char	*p;
	int		s ;
	long	n;

	n = nb;
	if (n == 0)
		return (ft_strdup("0"));
	s = size_calc(n);
	p = malloc(sizeof(char) * s + 1);
	if (!p)
		return (0);
	p[s] = '\0';
	if (n < 0)
	{
		p[0] = '-';
		n = -n;
	}
	while (n)
	{
		p[s - 1] = (n % 10) + 48;
		n /= 10;
		s--;
	}
	return (p);
}
