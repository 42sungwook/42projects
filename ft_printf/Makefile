# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 15:18:08 by sungwook          #+#    #+#              #
#    Updated: 2022/12/14 15:08:26 by sungwook         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c \
		ft_printf_utils.c

SRCS_B = ft_printf_bonus.c \
			ft_printf_di_bonus.c \
			ft_printf_p_bonus.c \
			ft_printf_s_bonus.c \
			ft_printf_u_bonus.c \
			ft_printf_x_bonus.c \
			ft_printf_utils_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

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

bonus:
	

.PHONY: all clean fclean re bonus