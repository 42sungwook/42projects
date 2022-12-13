# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 15:18:08 by sungwook          #+#    #+#              #
#    Updated: 2022/12/13 15:27:04 by sungwook         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c \
		ft_printf_utils.c

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

CC = cc

AR = ar -rcs

RM = rm -f

CFLAGS = -Wextra -Wall -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean:
	make clean
	$(RM) $(NAME)

re:
	make fclean 
	make all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re