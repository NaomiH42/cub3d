# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 16:54:08 by ehasalu           #+#    #+#              #
#    Updated: 2023/01/17 14:11:56 by ehasalu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft
LIBFTPRINTF = ./ft_printf/libftprintf.a
SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_strdup.c ft_substr.c ft_strlcpy.c ft_calloc.c ft_strtrim.c \
	ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_itoa.c ft_strjoin.c ft_strmapi.c ft_striteri.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c

SRCS_PRINTF = ./ft_printf/ft_putchar.c ./ft_printf/ft_putnbrun.c \
				./ft_printf/hexalow.c ./ft_printf/putmem.c ./ft_printf/ft_printf.c \
				./ft_printf/ft_putnbr.c ./ft_printf/ft_putstr.c ./ft_printf/hexaup.c \
				./ft_printf/perc.c ./ft_printf/printf_util.c ./ft_printf/printf_util2.c \
				./ft_printf/printf_util3.c ./ft_printf/printf_util4.c

SRCS_GNL = ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
OBJS_GNL = $(SRCS_GNL:.c=.o)
OBJS_PRINTF = $(SRCS_PRINTF:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_GNL) $(OBJS_PRINTF)
	@ar rc $(NAME).a $(OBJS) $(OBJS_GNL) $(OBJS_PRINTF)

%.o: %.c
	@$(CC) $(CFLAGS)  -c $< -o $@

clean:
	@rm -rf $(OBJS) $(OBJS_GNL) $(OBJS_PRINTF)

fclean: clean
	@rm -rf $(NAME).a

re: fclean all

.PHONY: all clean fclean re
