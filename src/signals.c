/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:21:48 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/11 14:37:11 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void sig_int_handler(int type)
{

	if (type == SIGINT)
	{
		// destroy the tree;
		// ft_putstr_fd("\n", STDOUT_FILENO);
		// rl_on_new_line();
        // rl_replace_line("", 0);
        // rl_redisplay();
		exit (app->status);
	}
}