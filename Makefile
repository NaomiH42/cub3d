NAME = cub3d

SRCS = main.c

CC = cc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) libmlx42.a libft.a -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

clean:
	rm -rf ${NAME}

fclean:	clean

re:	fclean all

.PHONY:	all clean fclean re
