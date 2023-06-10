/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:20:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/10 15:27:05 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../env/env.h"
# include "../libs/libft/libft.h"

# define SYNTAX_ERROR_EXIT_STATUS 258
# define COMMAND_NOT_FOUND_EXIT_STATUS 127
# define PIPE_READ_END 0
# define PIPE_WRITE_END 1
# define LEFT_CHILD 1
# define RIGHT_CHILD 2

# define SYNTAX_ERROR_MSG "shell : parse error near"
# define QUOTES_ERROR_MSG "Syntax Error , Quotes are not closed!"
# define PARENTICIES_ERROR_MSG "Syntax Error , parentheses are not closed!"

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
	UNK,
	EMPTY,
	WILDCARD,
	HEREDOC,
	SPACE,
	DOT
}					t_type;

typedef struct s_lexer
{
	char			*str;
	t_boolean		is_oper;
	t_boolean		is_builtin;
	t_type			type;
	int id;
	char			*path;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

typedef struct s_parser
{
	char			*str;
	char			*path;
	t_lexer			*args_list;
	t_type			type;
	t_boolean		is_builtin;
	t_boolean		is_op;
	int id;
	struct s_parser	*next;
	struct s_parser	*prev;
}					t_parser;

typedef struct s_tree
{
	char			*str;
	char			*path;
	t_lexer			*cmd_args;
	char			**args;
	t_boolean		is_op;
	int id;
	t_boolean		is_builtin;
	t_type			type;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_app
{
	t_env		*env_list;
	int			hdoc_fd;
	int			status;
}	t_app;


// main
t_tree				*formater(char *cmd);
int					ft_error(char *str);
void				ft_free_lexer_list(t_lexer **list);

// lexer functions
t_lexer				*lexer(char *args, t_env *env);
char				**all_paths(t_env *env);
void				ft_free(char **tabs);
void				add_token_to_end(t_lexer **head, t_lexer *new_token);
t_lexer				*create_token(char *str, int len, char **paths);
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
int					is_special_char(char c);
int					compare(t_lexer *item, char *oper);
char				**ft_mini_split(const char *src, char c);
t_lexer				*get_last_token(t_lexer *list);
int					is_operator(char c);
int					check_qoutes(t_lexer *list);
void				ft_trim_quotes(t_lexer *node);
int					check_pths(t_lexer *list);
void				set_type(t_lexer **list);
void				join_args(t_lexer **list, char **paths);
void				del_node(t_lexer *node);
void				clean_spaces(t_lexer **list);
int	is_space(char c);

// parser functions
t_parser			*parser(t_lexer *list);
void				print_parser_list(t_parser *list);
t_parser			*create_blocks(t_lexer *lexer_list);
t_lexer				*ft_nodedup(t_lexer *node);
void				add_node_to_list(t_parser **list, t_parser *item);
t_parser			*create_parser_node(t_lexer *l_node, int id);
void				ft_free_parser_list(t_parser **list);

// expander function
int					ft_expander(t_lexer *list, t_env *env);
char				*expand(char *var, t_env *envp);
void				ft_expand_vars(t_lexer **list, t_env *envp);
int					isabs(char *str);
char				*extract_cmd(char *cmd);
int					validate_cmd(char *cmd);
// syntax analizer
int					check_opeators(t_lexer *op);
int					check_pth(t_lexer *pt);
int					check_redir(t_lexer *rdir);
int					syntax_analyzer(t_lexer *list);
int					check_qoutes(t_lexer *list);

// ast
t_tree				*create_node(t_parser *item);
t_tree				*create_token_node(t_parser *node, t_tree *left,
						t_tree *right);
t_tree				*create_tree(t_parser **list);
t_tree				*term(t_parser **list);
t_tree				*factor(t_parser **list);
void				printTreeHelper(t_tree *root, int depth);
void				printTree(t_tree *root);

int					ft_char_search(char *str, char c);
int					ft_last_char_search(char *str, char c);

#endif
