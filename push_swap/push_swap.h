#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
	int num;
	int group;
	size_t idx;
	struct s_list *next;
} t_list;

typedef struct s_count
{
	size_t a;
	size_t b;
	size_t group2;
	size_t group4;
} t_count;

// ps_instructions
void ps_push(char *c, t_list **stack_add, t_list **stack_del, t_count *count);
void ps_rotate(char *c, t_list **stack, size_t num);
void ps_reverse_rotate(char *c, t_list **stack, size_t num);

// ps_utils
int ps_atoi(char *str);
t_list *ps_addlist(int num, int group, size_t idx);
int ps_check_dup(t_list *answer);
void find_best_a_to_b(t_list **stack_a, t_list **stack_b, t_count *count);

// ps_merge
void ps_merge_sort(t_list **list, size_t size);

// ps_main
void start_push_swap(t_list **stack_a, t_list **stack_b, t_count *count);
#endif