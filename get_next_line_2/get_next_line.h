#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 3

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;
