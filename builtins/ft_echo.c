/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:22:02 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/03/15 13:29:05 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char *data)
{
	// if no data new linw been printed
	if (!data)
		ft_putchar_fd('\n', 1);
	else //else the data been printed in stdout
		ft_putendl_fd(data, 1);
}
