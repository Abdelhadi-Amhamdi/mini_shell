NAME = app

libft_path = libft/
build_path = build/
srcs_path = parse/

header = parsing.h
src = lexer.c utils.c
srcs = $(addprefix $(srcs_path), $(src))

obj = $(src:.c=.o)
objs = $(addprefix $(build_path), $(obj))

libft = libft.a

#-fsanitize=address 

$(build_path)%.o : $(srcs_path)%.c
	cc -Wall -Wextra -Werror -c $< -o $@

all: $(NAME) 

$(NAME) : $(build_path) $(libft) $(objs)
	cc -Wall -Wextra -Werror $(objs) $(libft_path)$(libft) -o $@ 

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