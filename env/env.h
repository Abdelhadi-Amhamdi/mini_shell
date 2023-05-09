/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagouzou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:20:59 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/09 14:43:13 by aagouzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../libs/libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

t_env	*ft_new_node(char *key, char *val);
void	ft_add_back_env(t_env **list, t_env *item);
t_env	*get_env_vars(char **envp);
void	formate_env_item(char **key, char **val, char *item);
int ft_search(char *item, char tofind);

#endif