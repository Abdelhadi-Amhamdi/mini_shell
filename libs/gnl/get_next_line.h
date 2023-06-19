/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:58:08 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/17 20:47:09 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../../includes/mini_shell.h"

# define BUFFER_SIZE 42

char	*ft_join(char *s1, const char *s2);
int		ft_search_gnl(const char *data);
char	*get_next_line(int fd);

#endif