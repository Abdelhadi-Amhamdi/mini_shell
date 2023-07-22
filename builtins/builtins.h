/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:06:14 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/22 10:45:52 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../env/env.h"
# include "../includes/mini_shell.h"
# include "../parse/parsing.h"

int		ft_cd(t_env *env, t_tree *path, t_main *data);
int		ft_echo(t_tree *node, int out);
int		ft_env(t_env *env, int out);
int		ft_unset(t_tree *node, t_env *env);
int		ft_export(t_tree *cmd, t_env **env, int out);
int		ft_exit(t_tree *cmd, t_main *data);
int		ft_pwd(t_env *envp, int out, t_main *data);
void	print_export(t_env *env, int out);
int		check_digits(char *data);
int		is_all_space(char *s);
void	del_env_node(t_env *node);
void	print_err(char *string, int *exit_s);
int		is_exist(t_env *node, t_env *env);
t_env	*search_node(t_env *node, t_env *env);
int		check_key(char *key);
#endif