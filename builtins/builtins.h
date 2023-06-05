/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:06:14 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/05 14:41:19 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_cd(t_env *env, t_tree *path);
int	ft_echo(t_tree *node);
int	ft_env(t_env *env);
t_env	*ft_unset(t_tree	*node, t_env *env);
int	ft_export(t_tree *cmd, t_env **env);
int	ft_pwd(void);
void	ft_exit(void);


#endif