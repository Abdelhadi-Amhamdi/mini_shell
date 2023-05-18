/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:20:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/18 22:01:36 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../env/env.h"
# include "../libs/libft/libft.h"

typedef enum s_boolean
{
	false,
	true
}					t_boolean;

typedef enum s_type
{
	CMD,
	PIPE,
	RDIR,
	APND,
	AND,
	OR,
	ARGS,
	VAR,
	FL,
	SQ,
	DQ,
	OP,
	CP,
	UNK
}					t_type;

typedef struct s_lexer
{
	char			*str;
	t_boolean		is_oper;
	t_boolean		is_builtin;
	t_type			type;
	char			*path;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

typedef struct s_parser
{
	char			**str;
	char			*op;
	struct s_parser	*next;
	struct s_parser	*prev;
}					t_parser;

typedef struct s_tree
{
	char			*str;
	t_type			type;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

// main
t_parser			*formater(char *cmd, t_env *envp);

// lexer functions
t_lexer				*lexer(char *args, t_env *env);
char				**all_paths(t_env *env);
void				ft_free(char **tabs);
void				add_token_to_end(t_lexer **head, t_lexer *new_token);
t_lexer				*create_token(char *str, int is_token, char	**paths);
void				print_token_list(t_lexer *head);
char				**args_filter(char *str);
char				*filter_args_helper(char *str);
size_t				count_new_args_size(char *str);
char				*check_args(char *str);
t_type				check_type(t_lexer *lexer_item, char *path);
int					is_var(t_lexer *node);
int					is_builtin(char *cmd);
char				*get_path(char *cmd, char **paths);
int					check_op_prev(char *str, int i);
int					check_op_next(char *str, int i);
int					is_container(char c);
int					is_operator(char c);
int					compare(t_lexer	*item, char *oper);

// parser functions
t_parser			*parser(t_lexer *list, t_env *envp);
t_type				check_type(t_lexer *lexer_item, char *path);
void				print_parser_list(t_parser *list);
char				*get_path(char *cmd, char **paths);
// expander function
t_lexer				*ft_expander(t_lexer *list, t_env *env);

#endif
