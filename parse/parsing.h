/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:20:25 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/07/19 16:36:25 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../env/env.h"
# include "../libs/libft/libft.h"

# define SYNTAX_ERROR_EXIT_STATUS 258
# define COMMAND_NOT_FOUND_EXIT_STATUS 127
# define NO_PERMISSIONS_EXIT_STATUS 126
# define SUCCESS_EXIT_STATUS 0
# define FAILURE_EXIT_STATUS 1

# define PIPE_READ_END 0
# define PIPE_WRITE_END 1
# define LEFT_CHILD 1
# define RIGHT_CHILD 2

# define SYNTAX_ERROR_MSG "mini-sh : Syntax Error , parse error near "
# define QUOTES_ERROR_MSG "Syntax Error , Quotes are not closed!"
# define PARENTICIES_ERROR_MSG "Syntax Error , parentheses are not closed!"
# define AME " : ambiguous redirect"
# define NFD " : No such file or directory"
# define ISD " : is a directory"

# define DEL_HERDOC_NODE -11
# define PREINTABLE_SPACE -14
# define DONT_REMOVESP -15
# define DONT_EXPAND -16

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
	W_SPACE,
	DOT,
	HEREDOC_FILE
}					t_type;

typedef struct s_lexer
{
	char			*str;
	t_boolean		is_oper;
	t_boolean		is_builtin;
	t_type			type;
	int				id;
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
	int				id;
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
	int				id;
	t_boolean		is_builtin;
	t_type			type;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_pipes
{
	int				*pipe;
	struct s_pipes	*next;
}					t_pipes;

typedef struct main
{
	t_tree			*ast;
	t_env			*env;
	t_pipes			*pipes;
	int				open;
}					t_main;

t_tree				*formater(char *cmd, t_main *data);
int					ft_error(char *str);
void				_free_lexer(t_lexer **list);

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
void				ft_trim_quotes(t_lexer *node);
int					check_pths(t_lexer *list);
void				set_type(t_lexer **list);
void				join_args(t_lexer **list, char **paths);
void				del_node(t_lexer *node);
void				clean_spaces(t_lexer **list);
int					is_space(char c);
int					is_wild_card(t_lexer *node);
int					check_and_trim(t_lexer *tmp, char **paths);
void				_rebuild_node(t_lexer *tmp, char **paths);

int					all_inside_is_sp(t_lexer *tmp);
int					contain_only_qs(t_lexer *tmp);
void				is_printable_sp(t_lexer *tmp);
void				will_remove_sp(t_lexer *tmp);

t_lexer				*tokenizer(char *cmd, char **paths);
char				*ft_spaces(t_lexer **list, char *cmd, char **paths);
char				*ft_oneoperator(t_lexer **list, char *cmd, char c,
						char **paths);
char				*ft_parentheses(t_lexer **list, char *cmd, char **paths);
char				*ft_quotes(t_lexer **list, char *cmd, char c, char **paths);
char				*ft_variable(t_lexer **list, char *cmd, char **paths);

t_parser			*parser(t_lexer *list, t_main *data);
void				print_parser_list(t_parser *list);
t_parser			*create_blocks(t_lexer *lexer_list, t_main *data);
t_lexer				*ft_nodedup(t_lexer *node);
void				add_node_to_list(t_parser **list, t_parser *item);
t_parser			*create_parser_node(t_lexer *l_node, int id);
void				_free_parser(t_parser **list, int t);
t_parser			*create_blocks(t_lexer *lexer_list, t_main *data);
int					create_block_doc_helper(t_lexer *tmp,
						t_parser **parser_list, t_main *data);
t_lexer				*pass_args_to_cmd(t_lexer *ar, t_parser **new_node);
t_lexer				*add_new_simple_node(t_lexer *tmp, t_parser **parser_list);
int					ft_check_next(t_lexer *node, char *file_name);
void				heredoc_to_inrdir(t_parser **list, char *file_name);
t_lexer				*handle_rdir_case(t_parser **parser_list, t_lexer *arg,
						t_lexer **args_list);

int					ft_expander(t_lexer **list, t_env *env);
char				*expand(char *var, t_env *envp);
int					validate_cmd(char *cmd);
void				ft_expand_vars(t_lexer **list, t_env *envp, t_lexer *tmp);
int					ft_expand_wildcards(t_lexer **list);
char				*extarct_expand(char *cmd, int *i);
char				*extract_before(char *cmd, int *i);
char				*extarct_after(char *cmd, int *i);
void				expander_helper(t_lexer **list, t_lexer *tmp, char *var,
						t_env *envp);
int					contain_spaces(char *string);
char				*ft_get_expand_val(char *var, t_env *envp);
char				*join_variables(char **before, char **var, char **after);
void				normal_case_handler(char *string, t_lexer **list,
						t_lexer *tmp, t_env *envp);
void				ft_addup_to_list(t_lexer *new, t_lexer **list,
						t_lexer *node);
int					get_lenght(char *s, int *index);
void				add_middle_node(t_lexer *new, t_lexer *prev, t_lexer *next,
						t_lexer *last);

int					check_opeators(t_lexer *op);
int					check_pth(t_lexer *pt);
int					check_redir(t_lexer *rdir);
int					syntax_analyzer(t_lexer *list);
int					check_qoutes(t_lexer *list, char **paths);

t_tree				*create_node(t_parser *item);
t_tree				*create_token_node(t_parser *node, t_tree *left,
						t_tree *right);
t_tree				*factor(t_parser **list);
t_tree				*create_tree(t_parser **list);
t_tree				*termx(t_parser **list);
t_tree				*term(t_parser **list);
t_tree				*factor(t_parser **list);
void				printTreeHelper(t_tree *root, int depth);
void				printTree(t_tree *root);

int					ft_char_search(char *str, char c);
int					ft_last_char_search(char *str, char c);

void				ft_p_error(char *str, t_tree *file, int status);
void				set_null_value(t_lexer	*tmp);
void				p_error(char *str, t_lexer *tmp, int status);
void				re_link_list(t_lexer *tmp, \
t_lexer *new_list, t_lexer **list);

#endif
