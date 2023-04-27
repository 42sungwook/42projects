NAME		= minishell
CC          = cc
# CFLAGS      = -Wall -Wextra -Werror
RM			= rm -f
LIBFT		= -Llibft -lft
LFLAGS		= -lreadline

HEADER_DIR  = ./
HEADER_SRCS	= minishell.h
HEADER		= $(addprefix $(HEADER_DIR), $(HEADER_SRCS))

M_DIR		= ./
M_SRCS      = minishell.c init_structures.c free_functions.c
M_PATH		= $(addprefix $(M_DIR), $(M_SRCS))
M_OBJS		= $(M_PATH:c=o)


P_DIR 	 = ./parse_line
P_SRCS	 = end_of_word.c make_word.c parse_dollar.c parse_double_quote.c parse_pipe.c \
		   parse_redirection.c make_command.c
P_PATH	 = $(addprefix $(P_DIR)/, $(P_SRCS))
P_OBJS	 = $(P_PATH:c=o)

RESET = \033[0m
GREEN = \033[1;32m
CYAN = \033[1;36m


OBJS = $(M_OBJS) $(P_OBJS)


%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(G_OBJS) $(OBJS)
	@make -C libft all
	@$(CC) $(CFLAGS) $(LFLAGS) $(LIBFT) $(OBJS) -o $@
	@echo "$(GREEN)╔══════════════════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║       minishell compile finished :)      ║$(RESET)"
	@echo "$(GREEN)╠══════════════════════════════════════════╣$(RESET)"
	@echo "$(GREEN)║                                          ║$(RESET)"
	@echo "$(GREEN)║              Welcome to HELL             ║$(RESET)"
	@echo "$(GREEN)║                                          ║$(RESET)"
	@echo "$(GREEN)╚══════════════════════════════════════════╝$(RESET)"

all: $(NAME)

clean:
	@make -C libft clean
	@$(RM) $(G_OBJS)
	@$(RM) $(M_OBJS)
	@$(RM) $(P_OBJS)
	@echo "$(CYAN)╔════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║           make clean finished.         ║$(RESET)"
	@echo "$(CYAN)╚════════════════════════════════════════╝$(RESET)"

fclean:
	@make -C libft fclean
	@make clean
	@$(RM) $(NAME)
	@echo "$(CYAN)╔════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║          make fclean finished.         ║$(RESET)"
	@echo "$(CYAN)╚════════════════════════════════════════╝$(RESET)"

re:
	make fclean
	make all

.PHONY: all clean fclean re