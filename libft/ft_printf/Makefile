# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 16:54:08 by ehasalu           #+#    #+#              #
#    Updated: 2023/01/22 12:43:17 by ehasalu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf
SRCS =	ft_putchar.c ft_putnbrun.c hexalow.c putmem.c ft_printf.c ft_putnbr.c \
	ft_putstr.c hexaup.c ../ft_strlen.c perc.c printf_util.c printf_util2.c \
	printf_util3.c printf_util4.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

bonus: all

$(NAME): $(OBJS)
	ar rc $(NAME).a $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@	

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME).a

re: fclean all

.PHONY: all clean fclean re
