/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:06:14 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/11 15:17:36 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	ft_cd(t_env *env, t_parser *path);
void	ft_echo(t_parser *node);
void	ft_env(t_env *env);
t_env	*ft_unset(t_parser *node, t_env *env);
void	ft_export(t_parser *full_cmd, t_env **env);
void	ft_pwd(void);
void	ft_exit(void);


#endif