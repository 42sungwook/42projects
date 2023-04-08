SRCS = ./pipex.c ./ft_split.c ./open_files.c ./save_paths.c ./child_process.c
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