#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
	int num;
	int	group;
	size_t idx;
	struct s_list *next;
} t_list;

// ps_utils
int ps_atoi(char *str);
t_list *ps_addlist(int num);
int ps_check_duplist(t_list *answer);

// ps_merge
void ps_merge_sort(t_list **list, size_t size);

#endif