/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:20:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/05 16:22:21 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H
# include "../libft/libft.h"
# include "../env/env.h"


typedef enum s_boolean {false,true}	t_boolean;
typedef enum s_type {CMD,UNK,TOKEN,ARGS,VAR,FL,SQ,DQ}	t_type;

typedef struct s_lexer
{
	char			*str;
	t_boolean		is_token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_parser
{
	char			*str;
	t_type			type;
	char			*path;
	t_boolean		is_builtin;
	struct s_parser	*next;
	struct s_parser	*prev;
}	t_parser;

// main
t_parser	*formater(char *cmd, t_env *envp);

// lexer functions
t_lexer		*lexer(char *args);
char		**args_filter(char *str);
int			is_token(char c);


// parser functions
t_parser	*parser(t_lexer *list, t_env *envp);
int			is_builtin(char *cmd);
t_type		check_type(t_lexer *lexer_item, char *p);
void		print_parser_list(t_parser *list);


// expander function
void		ft_expander(t_parser *list, t_env *envp);

#endif