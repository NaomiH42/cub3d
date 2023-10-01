NAME = cub3d

SRCS = main.c map.c

CC = cc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) libmlx42.a libft.a -Iinclude -ldl -lglfw -pthread -lm -g -o $(NAME)

bonus: all

clean:
	rm -rf ${NAME}

fclean:	clean

re:	fclean all

.PHONY:	all clean fclean re
