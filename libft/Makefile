CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
HEADER = libft.h

SRCS = 	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
	   	ft_isprint.c \
	   	ft_strlen.c \
	   	ft_toupper.c \
	   	ft_tolower.c \
	   	ft_strchr.c \
	   	ft_strrchr.c \
		ft_memset.c \
		ft_memcmp.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_itoa.c \
		ft_split.c 

BONUS =	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
			
SRCS_OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)


ifdef BONUSFLAG
	ALLOBJS 	= $(SRCS_OBJS) $(BONUS_OBJS)
else
	ALLOBJS 	= $(SRCS_OBJS)
endif

all: $(NAME)

bonus:
	make BONUSFLAG=1 
	
$(NAME) : $(ALLOBJS)
	ar rcs $(NAME) $(ALLOBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

clean:
	rm -rf $(SRCS_OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re:
		make fclean
		make all

.PHONY: all bonus clean fclean re