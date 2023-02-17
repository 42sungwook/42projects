# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 19:30:21 by sungwook          #+#    #+#              #
#    Updated: 2023/02/17 19:30:22 by sungwook         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./ps_merge.c ./ps_utils.c ./push_swap.c ./ps_utils2.c ./ps_instructions.c ./push_swap_start.c ./ps_send_group.c

OBJS = $(SRCS:.c=.o)

NAME = push_swap

CC		=	cc -g -fsanitize=address
CFLAGS	=	-Wall -Werror -Wextra

all:	$(NAME)

$(NAME):	$(OBJS) ./push_swap.h
			$(CC) $(OBJS) -o $(NAME)

%.o : %.c
			$(CC) -c $< -o $@

clean:
			rm -rf $(NAME)
			rm -rf $(OBJS)

fclean:		clean

re:			fclean all

.PHONY:		all clean fclean re