Name = cub3d

srcs = main.c

OBJ = $(patsubst %.c, %.o, $(SOURCES))

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -IMLX42 -lXext -lX11 -lm -lz -o $(NAME)
