SRCS = ./minishell.c

OBJS = $(SRCS:.c=.o)

NAME = minishell

BONUS = checker

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
LFLAGS  =	-lreadline

all:	$(NAME)

bonus:	$(BONUS)

$(NAME):	$(OBJS) ./minishell.h
			@$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)
			@echo "\033[33mmake minishell\033[0m"


%.o : %.c
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -rf $(OBJS)
			@echo "\033[31mclean\033[0m"

fclean:
			@rm -rf $(OBJS)
			@rm -rf $(NAME)
			@echo "\033[31mdelete\033[0m"


re:			fclean
			@make all

.PHONY:		all clean fclean re