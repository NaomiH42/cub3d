NAME := cub3d

SRCS_DIR := ./src/

SRC := 	main.c map.c map2.c map3.c casting.c controls. controls2.c controls3_n_stuff.c drawing.c \
		minimap.c prep_prog.c raying.c

INCLUDE := ./include/

SRCS := $(addprefix $(SRCS_DIR), $(SRC))
OBJS := $(addsuffix .o,$(basename $(SRCS)))

CC := cc

CFLAGS := -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) libmlx42.a libft.a -Iinclude -ldl -lglfw -pthread -lm -g -o $(NAME)

%.o: %.c
				cc $(CFLAGS) -I $(INCLUDE) -c $< -o $@
bonus: all

clean:
	rm -rf ${NAME}

fclean:	clean

re:	fclean all

.PHONY:	all clean fclean re
