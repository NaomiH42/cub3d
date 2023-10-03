NAME := cub3d

MAKEFLAGS += --no-print-directory

SRCS_DIR := ./src/
OBJS_DIR := ./obj/
LIB_DIR := ./libs/

SRC := 	main.c map.c map2.c map3.c casting.c controls.c controls2.c controls3_n_stuff.c drawing.c \
		minimap.c prep_prog.c raying.c colors.c

INCLUDE := ./include/

SRCS := $(addprefix $(SRCS_DIR), $(SRC))
OBJS := $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))
CC := cc
LIBFT := $(LIB_DIR)libft.a
LIBMLX := $(LIB_DIR)libmlx42.a


CFLAGS := -Wall -Werror -Wextra

all: $(NAME)

print:
	$(info $(OBJS))
# make -n
# nm -C object_file

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	@$(CC) $(CFLAGS) -I$(INCLUDE) $(OBJS)  $(LIBMLX) $(LIBFT) -ldl -lglfw -pthread -lm -o $(NAME)
	@echo "Program prepared"

$(LIBFT):
	@make -C ./libft
	@mv ./libft/libft.a ./libs
	@echo "Compiling libft"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@cc -c $(CFLAGS) -I$(INCLUDE) $< -o $@

bonus: all

clean:
	@rm -rf ${NAME}

fclean:	clean
	@rm -rf $(OBJS)
	@rm -rf $(LIBFT)
	@make fclean -C ./libft

re:	fclean all

.PHONY:	all clean fclean re
