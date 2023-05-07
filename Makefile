NAME = app

libft_path = libs/libft/
build_path = build/
parsing_path = parse/
b_path = builtins/
srcs_path = src/
env_path = env/

header = parsing.h
p_src = lexer.c p_main.c parser.c parser_utils.c lexer_utils.c expander.c
env_src = v_main.c utils.c
src = main.c executer.c
b_src = ft_pwd.c ft_cd.c ft_echo.c

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
CC = cc

$(build_path)%.o : $(srcs_path)%.c
	cc -Wall -Wextra -Werror -c $< -o $@

$(build_path)%.o : $(parsing_path)%.c
	cc -Wall -Wextra -Werror -c $< -o $@

$(build_path)%.o : $(env_path)%.c
	cc -Wall -Wextra -Werror -c $< -o $@

$(build_path)%.o : $(b_path)%.c
	cc -Wall -Wextra -Werror -c $< -o $@

all: $(NAME) 

$(NAME) : $(build_path) $(libft) $(objs) $(p_objs) $(env_objs) $(b_objs)
	$(CC) $(CFLAGS) -lreadline $(objs) $(p_objs) $(env_objs) $(b_objs) $(libft_path)$(libft) -o $@ 

$(libft):
	make -s -C $(libft_path)
	make clean -s -C $(libft_path)

$(build_path):
	mkdir $(build_path)

clean:
	rm -rf $(build_path)

fclean: clean
	rm -f $(NAME)

re: fclean all