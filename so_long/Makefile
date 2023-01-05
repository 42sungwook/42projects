SRCS = 	./draw/draw_map.c ./draw/draw_user_move.c ./draw/draw_user.c \
		./draw/draw_utils.c ./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c ./initialize/init_val.c \
		./initialize/init_img.c	./so_long.c ./make_map/read_map.c \
		./make_map/make_deque_1.c ./make_map/make_deque_2.c \
		./make_map/map_check_way.c ./make_map/map_check.c ./utils/utils.c \
		./utils/ft_itoa.c ./case_check/case_check.c ./case_check/case_check2.c

SRCS_B = ./draw/draw_map_bonus.c ./draw/draw_user_move_bonus.c ./draw/draw_user_bonus.c \
		./draw/draw_utils_bonus.c ./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c ./initialize/init_val_bonus.c \
		./initialize/init_img_bonus.c	./so_long_bonus.c ./make_map/read_map_bonus.c \
		./make_map/make_deque_1_bonus.c ./make_map/make_deque_2_bonus.c \
		./make_map/map_check_way_bonus.c ./make_map/map_check_bonus.c ./utils/utils_bonus.c \
		./utils/utils2_bonus.c ./case_check/case_check_bonus.c ./case_check/case_check2_bonus.c \
		./draw/draw_enemy_bonus.c ./initialize/init_enemy_bonus.c ./draw/draw_enemy2_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

NAME = so_long

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
CLIB	=	-L./mlx -lmlx -framework OpenGL -framework Appkit

ifdef BONUS
 	OBJS_ALL = $(OBJS_B)
else
	OBJS_ALL = $(OBJS)
endif

all:	$(NAME)

$(NAME):	$(OBJS_ALL)
			$(CC) $(CFLAGS) $(CLIB) $(OBJS_ALL) -o $(NAME)

%.o : %.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -rf $(NAME)
			rm -rf $(OBJS) $(OBJS_B)

fclean:		clean

re:			fclean all

bonus:
	make BONUS=1 all

.PHONY:		all clean fclean re bonus