/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 23:35:19 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/19 16:35:16 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_put_strerror(char *cmd, char *str)
{
	ft_putstr_fd("mini-sh: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(str, 2);
}

void	perror_sstatus(int status, t_boolean is_built)
{
	status = WEXITSTATUS(status);
	if (status && g_exit_status == -1)
		g_exit_status = status;
	else if (status && g_exit_status != -1)
	{
		if (status == ENOENT && !is_built)
			g_exit_status = COMMAND_NOT_FOUND_EXIT_STATUS;
		else if (status == EACCES && !is_built)
		{
			ft_putstr_fd("mini-sh: ", 2);
			ft_putendl_fd(strerror(status), 2);
			g_exit_status = NO_PERMISSIONS_EXIT_STATUS;
		}
		else
			g_exit_status = status;
	}
	else
		g_exit_status = SUCCESS_EXIT_STATUS;
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
	g_exit_status = 0;
	data = malloc(sizeof(t_main));
	if (!data)
		return (NULL);
	data->env = get_env_vars(env);
	data->ast = NULL;
	data->pipes = NULL;
	data->open = 0;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	return (data);
}

int	expand_vars(t_tree *file, t_main *data)
{
	char		*tmp;
	struct stat	file_stat;

	if (file && file->type == VAR)
	{
		tmp = file->str;
		file->str = expand(file->str, data->env);
		if (!file->str)
		{
			file->id = -1;
			return (free (tmp), 1);
		}
		else if (contain_spaces(file->str))
			return (ft_p_error(AME, file, -1), free(tmp), 1);
		else
		{
			if (stat(file->str, &file_stat) == 0)
			{
				if (S_ISDIR(file_stat.st_mode))
					return (ft_p_error(ISD, file, -1), free(tmp), 1);
			}
		}
		free(tmp);
	}
	return (0);
}
