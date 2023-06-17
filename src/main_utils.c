/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 23:35:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/17 11:31:36 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	perror_sstatus(int status, char *cmd)
{
	status = WEXITSTATUS(status);
	if (status)
	{
		printf("mini-sh: %s: %s\n", cmd, strerror(status));
		if (status == ENOENT)
			exit_status = COMMAND_NOT_FOUND_EXIT_STATUS;
		else if (status == EACCES)
			exit_status = NO_PERMISSIONS_EXIT_STATUS;
		else
			exit_status = FAILURE_EXIT_STATUS;
	}
	else
		exit_status = SUCCESS_EXIT_STATUS;
}

t_wildcard_data	init_data(void)
{
	t_wildcard_data	data;

	data.str_index = 0;
	data.cnd_index = 0;
	data.next_card = -1;
	data.backtrack = -1;
	return (data);
}

t_main	*init(char **env, int ac, char **av)
{
	t_main	*data;

	(void)ac;
	(void)av;
	exit_status = 0;
	data = malloc(sizeof(t_main));
	if (!data)
		return (NULL);
	data->env = get_env_vars(env);
	data->ast = NULL;
	data->pipes = NULL;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	return (data);
}
