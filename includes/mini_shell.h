/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:13:34 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/26 11:53:44 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include "../builtins/builtins.h"
# include "../env/env.h"
# include "../libs/gnl/get_next_line.h"
# include "../libs/libft/libft.h"
# include "../parse/parsing.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

int				g_exit_status;

typedef struct s_pdata
{
	int			used_end;
	int			unused_end;
	int			out;
	int			std_file;
	int			side;
}				t_pipe_data;

typedef struct wildcard_data
{
	int			str_index;
	int			cnd_index;
	int			next_card;
	int			backtrack;
}				t_wildcard_data;

# define HEREDOC_FILENAME "/tmp/heredoc_file"

void			run_pipeline(t_tree *pipe_node, int out, t_main *data);
void			run_pipe(t_tree *cmd, int *pipe, t_pipe_data p_data,
					t_main *data);
void			exec_rdir_pipes(t_pipe_data p_data, t_tree *cmd, t_main *data);
void			exec_pipe_cmd(t_tree *cmd, t_pipe_data p_data, t_main *data);
void			exec_cmd(t_tree *node, t_main *data);
t_pipes			*pipe_node_create(int **pipe);
void			add_to_end(t_pipes **list, t_pipes *item);
void			wait_for_last(t_tree *cmd_right);
void			close_all_pipes(t_main *data, int fd1, int fd2);
void			exec_pipe_unk(t_tree *cmd, t_pipe_data p_data, t_main *data);

void			executer(t_tree *root, t_main *data);
void			executer_helper(t_tree *root, int in, int out, t_main *data);
void			exec_unknown(t_tree *cmd, int in, int out, t_main *data);
int				exec_builtin(t_tree *cmd, t_env **env, t_main *data, int out);
void			run_cmd(t_tree *cmd, int in, int out, t_main *data);
int				_args_size(t_lexer *list);
int				path_exist(char *path, char **paths);
char			**env_tabs(t_env *list);
char			**_args_tabs(t_tree *node, t_main *data);
char			*exit_status_expand(t_lexer *node);
char			*_path(t_tree *node, t_main *data);
int				check_path_exist(char *path, char **paths);
void			expand_var_to_cmd(t_tree *cmd, t_main *data);
void			_files(t_tree *root, int t, t_main *data);
char			*none_str(t_tree *node, t_main *data, char **paths);
void			_exec_unk(t_tree *cmd, int in, int out, t_main *data);
void			_exec(t_tree *cmd, int in, int out, t_main *data);

void			perror_sstatus(int status, char *cmd);

int				_get_rdir_file_fd(t_tree *node);
t_lexer			*creat_lexer_node(char *data);
void			rdir_helper(t_tree *root, int in, int out, t_main *data);

void			run_connectors(t_tree *root, int in, int out, t_main *data);

char			*wildcard(char *condition);
int				allow_hidden(char *file_name, char *cnd);
int				is_match(char *str, char *cnd);
int				check_end(t_wildcard_data data, char *cnd);
char			*ft_strjoin_entrys(char const *s1, char const *s2);
t_wildcard_data	init_data(void);

void			sig_int_handler(int type);
void			sigint_heredoc_handler(int type);

char			*start_heredoc(t_lexer *node,
					t_boolean to_expand,
					t_main *data);
int				run_heredoc(char *del, t_boolean to_expand, char *file_name,
					t_main *data);
char			*wait_heredoc(char *file_name, pid_t pid);
char			*ft_read_line(int fd);
void			_add_doc_to_end(t_lexer **head, t_lexer *new_item);
t_lexer			*_create_doc(char *data, t_type type);

void			wait_pids(t_tree *root);
t_main			*destroy_main(t_main *main, int t);
void			destroy_pipes(t_pipes *list);
void			destroy_ast_tree(t_tree *root);
t_main			*init(char **env, int ac, char **av);
void			wait_for_child(t_tree *cmd);

int				env_list_size(t_env *list);

int				*_ft_pipe(t_main *data);
int				_ft_dup2(int new, int old);
int				_ft_fork(void);
int				expand_vars(t_tree *file, t_main *data);
void			ft_put_strerror(char *cmd, char *str);

#endif