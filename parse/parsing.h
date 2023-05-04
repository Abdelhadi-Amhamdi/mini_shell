/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:20:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/04 11:40:27 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H
# include "../libft/libft.h"


typedef enum s_boolean {false,true}	t_boolean;

typedef struct s_lexer
{
	char			*str;
	t_boolean		is_token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;


char **args_filter(char *str);
int	is_token(char c);

#endif