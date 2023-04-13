SRCS = ./pipex.c ./ft_split.c ./utils.c ./main.c
OBJS = $(SRCS:.c=.o)

NAME = pipex

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra

all:	$(NAME)

$(NAME):	$(OBJS) ./pipex.h
			$(CC) $(OBJS) -o $(NAME)

%.o : %.c
			$(CC) -c $< -o $@

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re