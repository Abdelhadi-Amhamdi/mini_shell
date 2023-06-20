/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:06:14 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/19 21:28:39 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../env/env.h"
# include "../includes/mini_shell.h"
# include "../parse/parsing.h"

int		ft_cd(t_env *env, t_tree *path);
int		ft_echo(t_tree *node, int out);
int		ft_env(t_env *env, int out);
t_env	*ft_unset(t_tree *node, t_env *env);
int		ft_export(t_tree *cmd, t_env **env, int out);
void	ft_exit(t_tree *cmd, t_tree *tree);
int		ft_pwd(t_env *envp, int out);
void	print_export(t_env *env, int out);
int		check_digits(char *data);
int		is_all_space(char *s);
#endif