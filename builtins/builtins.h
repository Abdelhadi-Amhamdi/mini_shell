/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:06:14 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/13 15:52:08 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_cd(t_env *env, t_tree *path);
int	ft_echo(t_tree *node);
int	ft_env(t_env *env);
t_env	*ft_unset(t_tree	*node, t_env *env);
int	ft_export(t_tree *cmd, t_env **env);

void	ft_exit(t_tree *cmd, t_tree *tree);
int	ft_pwd(t_env	*envp);



#endif