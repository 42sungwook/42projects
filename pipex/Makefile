# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/15 14:11:02 by sungwook          #+#    #+#              #
#    Updated: 2023/04/15 17:09:50 by sungwook         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./ft_split.c ./main.c ./pipex.c ./utils.c ./utils2.c
SRCS_B = ./bonus/ft_split_bonus.c ./bonus/main_bonus.c ./bonus/pipex_bonus.c \
			./bonus/utils_bonus.c ./bonus/utils2_bonus.c ./bonus/heredoc_bonus.c \
			./bonus/get_next_line_bonus.c ./bonus/get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

NAME = pipex

CC		=	gcc -g
CFLAGS	=	-Wall -Werror -Wextra

ifdef BONUS
 	OBJS_ALL = $(OBJS_B)
else
	OBJS_ALL = $(OBJS)
endif

all:	$(NAME)

$(NAME):	$(OBJS_ALL)
			$(CC) $(CFLAGS) $(OBJS_ALL) -o $(NAME)

%.o : %.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -rf $(OBJS) $(OBJS_B)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

bonus:
	make BONUS=1 all

.PHONY:		all clean fclean re bonus