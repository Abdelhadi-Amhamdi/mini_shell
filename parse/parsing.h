/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:20:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/04 13:42:05 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H
# include "../libft/libft.h"


typedef enum s_boolean {false,true}	t_boolean;
typedef enum s_type {CMD,UNK,TOKEN,ARGS}	t_type;

typedef struct s_lexer
{
	char			*str;
	t_boolean		is_token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_parser
{
	char			**str;
	char			*type;
	char			*path;
	t_boolean		is_builtin;
	struct s_parser	*next;
	struct s_parser	*prev;
}	t_parser;

// lexer functions
char	**args_filter(char *str);
int		is_token(char c);


// parser functions
void	parser(t_lexer *lexer_list, char **envp);

#endif