SRCS = ./ps_merge.c ./ps_utils.c ./push_swap.c ./ps_utils2.c ./ps_instructions.c ./push_swap_start.c

OBJS = $(SRCS:.c=.o)

NAME = push_swap

CC		=	cc -g
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