NAME		= philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM			= rm -f

HEADER_DIR  = ./
HEADER_SRCS	= philo.h
HEADER		= $(addprefix $(HEADER_DIR), $(HEADER_SRCS))

M_DIR		= ./
M_SRCS      = main.c init_functions.c utils.c
M_PATH		= $(addprefix $(M_DIR), $(M_SRCS))
M_OBJS		= $(M_PATH:c=o)

RESET = \033[0m
GREEN = \033[1;32m
CYAN = \033[1;36m


OBJS = $(M_OBJS)


%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LFLAGS) $(LIBFT) $(OBJS) -o $@
	@echo "$(GREEN)╔══════════════════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║          philo  compile finished :)      ║$(RESET)"
	@echo "$(GREEN)╠══════════════════════════════════════════╣$(RESET)"
	@echo "$(GREEN)║                                          ║$(RESET)"
	@echo "$(GREEN)║              Welcome to HELL             ║$(RESET)"
	@echo "$(GREEN)║                                          ║$(RESET)"
	@echo "$(GREEN)╚══════════════════════════════════════════╝$(RESET)"

all: $(NAME)

clean:
	@$(RM) $(OBJS)
	@echo "$(CYAN)╔════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║           make clean finished.         ║$(RESET)"
	@echo "$(CYAN)╚════════════════════════════════════════╝$(RESET)"

fclean:
	@make clean
	@$(RM) $(NAME)
	@echo "$(CYAN)╔════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║          make fclean finished.         ║$(RESET)"
	@echo "$(CYAN)╚════════════════════════════════════════╝$(RESET)"

re:
	make fclean
	make all

.PHONY: all clean fclean re