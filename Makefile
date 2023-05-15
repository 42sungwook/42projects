# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/27 15:58:46 by daijeong          #+#    #+#              #
#    Updated: 2023/05/15 21:09:36 by daijeong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC          = cc -g
CFLAGS      = -Wall -Wextra -Werror -Ilibft -I${HOME}/.brew/opt/readline/include
RM			= rm -f
LIBFT		= -Llibft -lft
LFLAGS		= -lreadline -L${HOME}/.brew/opt/readline/lib

HEADER_DIR  = ./
HEADER_SRCS	= minishell.h
HEADER		= $(addprefix $(HEADER_DIR), $(HEADER_SRCS))

M_DIR		= ./
M_SRCS      = minishell.c init_structures.c free_functions.c free_arr.c merge_sort.c utils.c signal.c \
			  heredoc_signal.c
M_PATH		= $(addprefix $(M_DIR), $(M_SRCS))
M_OBJS		= $(M_PATH:c=o)


P_DIR 	 = ./parse_line
P_SRCS	 = end_of_word.c make_word.c parse_dollar.c parse_double_quote.c parse_pipe.c \
		   parse_redirection.c make_command.c parse_single_quote.c parse_question.c
P_PATH	 = $(addprefix $(P_DIR)/, $(P_SRCS))
P_OBJS	 = $(P_PATH:c=o)

E_DIR	= ./execute_cmds
E_SRCS	= execute_cmds.c heredoc.c pipex.c save_cmds.c first_child_process.c \
		  nth_child_process.c last_child_process.c save_fds.c close_fds.c
E_PATH	= $(addprefix $(E_DIR)/, $(E_SRCS))
E_OBJS	= $(E_PATH:c=o)

B_DIR	= ./builtin
B_SRCS	= check_builtins.c builtin_cd.c builtin_echo.c builtin_env.c builtin_pwd.c builtin_unset.c \
		  builtin_export.c envp_list_utils.c
B_PATH	= $(addprefix $(B_DIR)/, $(B_SRCS))
B_OBJS	= $(B_PATH:c=o)

RESET = \033[0m
GREEN = \033[1;32m
CYAN = \033[1;36m


OBJS = $(M_OBJS) $(P_OBJS) $(E_OBJS) $(B_OBJS)


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
	@$(RM) $(E_OBJS)
	@$(RM) $(B_OBJS)
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