# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 15:18:08 by sungwook          #+#    #+#              #
#    Updated: 2022/11/29 20:53:47 by sungwook         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_itoa.c \
		ft_putnbr.c \
		ft_utils.c \
		ft_printf.c

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

CC = cc

AR = ar -rcs

RM = rm -f

FLAGS = -Wextra -Wall -Werror

all:	$(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $<

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:
	make clean
	$(RM) $(NAME)

re:	
	make fclean 
	make all

bonus:	$(NAME)

.PHONY: all clean fclean re