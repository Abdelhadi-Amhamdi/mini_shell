NAME = app

libft_path = libs/libft/
build_path = build/
parsing_path = parse/
b_path = builtins/
srcs_path = src/
env_path = env/

header = parsing.h
p_src = lexer.c p_main.c parser.c parser_utils.c lexer_utils.c expander.c lexer_utils1.c lexer_utils2.c
env_src = env_main.c utils_env.c
src = main.c executer.c
b_src = ft_pwd.c ft_cd.c ft_echo.c ft_env.c ft_export.c ft_unset.c

p_srcs = $(addprefix $(parsing_path), $(p_src))
env_srcs = $(addprefix $(env_path), $(env_src))
srcs = $(addprefix $(srcs_path), $(src))
b_srcs = $(addprefix $(b_path), $(b_src))

obj = $(src:.c=.o)
p_obj = $(p_src:.c=.o)
b_obj = $(b_src:.c=.o)
env_obj = $(env_src:.c=.o)

objs = $(addprefix $(build_path), $(obj))
p_objs = $(addprefix $(build_path), $(p_obj))
b_objs = $(addprefix $(build_path), $(b_obj))
env_objs = $(addprefix $(build_path), $(env_obj))

libft = libft.a

#-fsanitize=address 
CFLAGS = -Wall -Wextra -Werror
CC = cc -g

$(build_path)%.o : $(srcs_path)%.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

$(build_path)%.o : $(parsing_path)%.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

$(build_path)%.o : $(env_path)%.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

$(build_path)%.o : $(b_path)%.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

all: $(NAME) 

$(NAME) : $(build_path) $(libft) $(objs) $(p_objs) $(env_objs)
	$(CC) $(CFLAGS) -lreadline $(objs) $(p_objs) $(env_objs) $(libft_path)$(libft) -o $@ 

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