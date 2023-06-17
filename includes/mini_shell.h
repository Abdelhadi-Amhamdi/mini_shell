/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:13:34 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/17 11:38:49 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include "../parse/parsing.h"
# include "../builtins/builtins.h"
# include "../env/env.h"
# include "../libs/libft/libft.h"
# include "../libs/gnl/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>

int	exit_status;

typedef struct s_pdata
{
	int	used_end;
	int	unused_end;
	int	out;
	int	std_file;
	int	side;
}	t_pipe_data;

typedef struct wildcard_data
{
	int	str_index;
	int	cnd_index;
	int	next_card;
	int	backtrack;
}	t_wildcard_data;

# define HEREDOC_FILENAME "/tmp/heredoc_file"

// pipes && pipes utils
void			run_pipeline(t_tree *pipe_node, int out, t_main *data);
void			run_pipe(t_tree *cmd, int *pipe, \
t_pipe_data p_data, t_main *data);
void			exec_rdir_pipes(t_tree *cmd, int \
used_end, int side, t_main *data);
void			exec_pipe_cmd(t_tree *cmd, t_pipe_data p_data, t_main *data);
void			exec_cmd(t_tree *node, t_main *data);
t_pipes			*pipe_node_create(int **pipe);
void			add_to_end(t_pipes **list, t_pipes *item);

// ececuteur and exec_utils
void			executer(t_tree *root, int in, int out, t_main *data);
void			exec_unknown(t_tree *cmd, int in, int out, t_main *data);
int				exec_builtin(t_tree	*cmd, t_env	**env, t_main *data, int out);
void			run_cmd(t_tree *cmd, int in, int out, t_main *data);
void			close_all_pipes(t_main *data, int fd1, int fd2);
int				_args_size(t_lexer *list, int is_b);
int				path_exist(char *path, char **paths);
char			**env_list_to_tabs(t_env *list);
char			**cmd_args_list_to_tabs(t_tree *node, t_main *data);
char			*mini_expander(t_lexer *node, t_main *data);
char			*_path(t_tree *node, t_main *data);
int				check_path_exist(char *path, t_main *data);
void			perror_sstatus(int status, char *cmd);

// redirections
void			redirection_helper(t_tree *node, int in, int out, t_main *data);
void			run_apand_function(t_tree *node, int in, int out, t_main *data);
void			run_redir_output(t_tree *node, int in, int out, t_main *data);
void			run_redir_input(t_tree *node, int in, int out, t_main *data);
t_lexer			*creat_lexer_node(char *data);

// connectors
void			run_connectors(t_tree *root, int in, int out, t_main *data);
void			wait_left(t_tree *root);

// wildcards
char			*wildcard(char *condition);
int				allow_hidden(char *file_name, char *cnd);
int				is_match(char *str, char *cnd);
int				check_end(t_wildcard_data data, char *cnd);
char			*ft_strjoin_entrys(char const *s1, char const *s2);
t_wildcard_data	init_data(void);

// signals
void			sig_int_handler(int type);
void			sigint_heredoc_handler(int type);

// heredoc
char			*start_heredoc(t_lexer *node, \
t_boolean to_expand, t_main *data);
int				run_heredoc(char *del, t_boolean \
to_expand, int fd, t_main *data);
char			*wait_heredoc(char *file_name, pid_t pid);
char			*ft_read_line(int fd);

// main
void			wait_pids(t_tree *root);
void			destroy_main(t_main *main);
void			destroy_pipes(t_pipes *list);
void			destroy_ast_tree(t_tree *root);
t_main			*init(char **env, int ac, char **av);

// env
int				env_list_size(t_env *list);

#endif