NAME = app

libft_path = libs/libft/
gnl_path = libs/gnl/
build_path = build/
parsing_path = parse/
b_path = builtins/
srcs_path = src/
env_path = env/
flags =   # -Wuninitialized -fsanitize=address,undefined,integer -g

# L = -L/Users/aagouzou/.brew/Cellar/readline/8.2.1/lib
# I = -I/Users/aagouzou/.brew/Cellar/readline/8.2.1/include

L = -L/Users/aamhamdi/.brew/Cellar/readline/8.2.1/lib
I = -I/Users/aamhamdi/.brew/Cellar/readline/8.2.1/include

header = parsing.h

# parsing files
p_src = lexer.c p_main.c parser.c parser_utils.c lexer_utils.c expander.c \
lexer_utils1.c lexer_utils2.c expander_utils.c tokenizer.c tokenizer_utils.c \
cleaner.c create.c reconstruct.c free.c tree.c analyzer.c blocks.c \
expand_wildcard.c expand_helper.c type.c blocks_utils.c tree_utils.c reconstruct_utils.c create_utils.c

# env files
env_src = env_main.c utils_env.c

# main files
src = main.c executer.c exec_utils.c  connectors.c heredoc.c rdir.c \
pipes.c signals.c wildcards.c main_utils.c pipes_utils.c heredoc_utils.c \
exec_utils1.c

# get next line files
g_src = get_next_line.c get_next_line_utils.c

# builtins files
b_src = ft_pwd.c ft_cd.c ft_echo.c ft_env.c ft_export.c ft_unset.c ft_exit.c builtins_utlis.c

p_srcs = $(addprefix $(parsing_path), $(p_src))
env_srcs = $(addprefix $(env_path), $(env_src))
srcs = $(addprefix $(srcs_path), $(src))
b_srcs = $(addprefix $(b_path), $(b_src))
g_srcs = $(addprefix $(gnl_path), $(g_src))

obj = $(src:.c=.o)
p_obj = $(p_src:.c=.o)
b_obj = $(b_src:.c=.o)
g_obj = $(g_src:.c=.o)
env_obj = $(env_src:.c=.o)

objs = $(addprefix $(build_path), $(obj))
p_objs = $(addprefix $(build_path), $(p_obj))
b_objs = $(addprefix $(build_path), $(b_obj))
g_objs = $(addprefix $(build_path), $(g_obj))
env_objs = $(addprefix $(build_path), $(env_obj))

libft = libft.a

#-fsanitize=address 
CFLAGS = -Wall -Wextra -Werror
CC = cc -g

$(build_path)%.o : $(srcs_path)%.c
	$(CC) -Wall -Wextra -Werror $(flags) -c $< -o $@ $(I)

$(build_path)%.o : $(parsing_path)%.c
	$(CC) -Wall -Wextra -Werror $(flags) -c $< -o $@ $(I)

$(build_path)%.o : $(env_path)%.c
	$(CC) -Wall -Wextra -Werror $(flags) -c $< -o $@ $(I)

$(build_path)%.o : $(b_path)%.c
	$(CC) -Wall -Wextra -Werror $(flags) -c $< -o $@ $(I)

$(build_path)%.o : $(gnl_path)%.c
	$(CC) -Wall -Wextra -Werror $(flags) -c $< -o $@ $(I)

all: $(NAME) 

$(NAME) : $(build_path) $(libft) $(objs) $(p_objs) $(env_objs) $(b_objs) $(g_objs)
	$(CC) $(CFLAGS) $(flags) $(objs) $(p_objs)  $(env_objs) $(b_objs) $(g_objs) $(libft_path)$(libft) -o $@ -lreadline $(L)

$(libft):
	make -s -C $(libft_path)
	make clean -s -C $(libft_path)

$(build_path):
	mkdir $(build_path)

clean:
	rm -rf $(build_path)

fclean: clean
	rm -f $(NAME)
	make fclean -s -C $(libft_path)

re: fclean all