/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:18:18 by aamhamdi          #+#    #+#             */
/*   Updated: 2022/10/26 11:10:11 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_if_overflow(long prev, long res)
{
	if (res / 10 == prev)
		return (0);
	return (1);
}

static const char	*trim_white_space(const char *s, int *sign)
{
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			*sign = -1;
		s++;
	}
	return (s);
}

int	ft_atoi(const char *s)
{
	int		sign;
	long	result;
	long	prev;

	result = 0;
	sign = 1;
	s = trim_white_space(s, &sign);
	while (*s >= '0' && *s <= '9')
	{
		prev = result;
		result = (result * 10) + (*s - 48);
		if (check_if_overflow(prev, result) == 1)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		s++;
	}
	return (result * sign);
}
