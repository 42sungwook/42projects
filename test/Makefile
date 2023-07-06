# **************************************************************************** #
# ProgramName && Files                                                         #
# **************************************************************************** #

INC_FILES	=
CLIENT_FILES =	client.c
SERVER_FILES =	server.c

# **************************************************************************** #
# Directories && Paths                                                         #
# **************************************************************************** #

INC_DIR =	include/
SRC_DIR =
OBJ_DIR =	.obj/
DEP_DIR =	.dep/

CLIENT_SRCS	=	$(addprefix $(SRC_DIR), $(CLIENT_FILES))
CLIENT_OBJS	=	$(CLIENT_FILES:%.c=$(OBJ_DIR)%.o)
CLIENT_DEPS	=	$(CLIENT_FILES:%.c=$(DEP_DIR)%.d)

SERVER_SRCS	=	$(addprefix $(SRC_DIR), $(SERVER_FILES))
SERVER_OBJS	=	$(SERVER_FILES:%.c=$(OBJ_DIR)%.o)
SERVER_DEPS	=	$(SERVER_FILES:%.c=$(DEP_DIR)%.d)

# **************************************************************************** #
# Compiler && flags                                                            #
# **************************************************************************** #
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -std=c99
CPPFLAGS	=	-I$(INC_DIR)
DEPFLAGS	=	-MMD -MP -MF $(@:$(OBJ_DIR)%.o=$(DEP_DIR)%.d)
RM			=	rm -rf

# **************************************************************************** #
# Debug options                                                                #
# **************************************************************************** #
ifdef DEBUG
	CFLAGS += -g
endif

# **************************************************************************** #
# Output controls                                                              #
# **************************************************************************** #
NAME_LEN = $(shell echo $(NAME) | tr -d '\n' | wc -c)
ifeq ($(shell echo "$(NAME_LEN)-6" | bc | grep -c '-'), 1)
	N = 6
else
	N = $(NAME_LEN)
endif
RST =	\033[0m
GRN =	\033[1;32m
CYN =	\033[1;36m
BCY =	\033[1;96m
HOM =	\033[A
CLR =	\033[K

# **************************************************************************** #
# Rules                                                                        #
# **************************************************************************** #
.DEFAULT_GOAL	=	all

-include $(CLIENT_DEPS)
-include $(SERVER_DEPS)

all: client server

client: $(CLIENT_OBJS)
	@$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS)
	@printf "$(CLR)$(GRN)%$Ns is Ready ✅\\n$(RST)" $@

server: $(SERVER_OBJS)
	@$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS)
	@printf "$(CLR)$(GRN)%$Ns is Ready ✅\\n$(RST)" $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	@printf "$(CLR)$(GRN)%$Ns is Ready : $<$(RST)$(HOM)\\n" $(NAME)
	@$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@$(RM) $(OBJ_DIR) $(DEP_DIR) *.dSYM
	@printf "$(CYN)%$Ns Objects! 🗑$(RST)\\n" Remove

fclean: clean
	@$(RM) client server
	@printf "$(BCY)%$Ns Programs! 🗑$(RST)\\n" Remove

re: fclean
	@make all

.PHONY: all client server clean fclean re