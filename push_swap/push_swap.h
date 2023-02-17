#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
	int				num;
	int				group;
	size_t			idx;
	struct s_list	*next;
}	t_list;

typedef struct s_count
{
	size_t	a;
	size_t	b;
	size_t	group1;
	size_t	group2;
	size_t	group3;
	size_t	group4;
	size_t	g1_start_idx;
	size_t	g2_start_idx;
	size_t	g3_start_idx;
	size_t	g4_start_idx;
}	t_count;

// ps_instructions
void	ps_push(char *c, t_list **stack_add, t_list **stack_del, t_count *count);
void	ps_rotate(char *c, t_list **stack, size_t num);
void	ps_reverse_rotate(char *c, t_list **stack, size_t num);

// ps_utils
int		ps_atoi(char *str);
t_list	*ps_addlist(int num, int group, size_t idx);
int		ps_check_dup(t_list *answer);
void	ps_uncount_group(t_list *stack_a, t_count *count);
void	print_stacks(t_list *stack_a, t_list *stack_b);
void	ps_init_count(t_count *count);
int		ps_check_for_group4(t_list *stack_a, size_t current_idx);

// ps_send_group
void	send_group1_to_a(t_list **stack_a, t_list **stack_b, t_count *count);
void	send_group2_to_a(t_list **stack_a, t_list **stack_b, t_count *count);
void	send_group3_to_a(t_list **stack_a, t_list **stack_b, t_count *count);
void	find_best_a_to_b(t_list **stack_a, t_list **stack_b, t_count *count, size_t current_idx);
void	find_best_b_to_a(t_list **stack_a, t_list **stack_b, t_count *count, size_t current_idx);

// ps_merge
void	ps_merge_sort(t_list **list, size_t size);

// ps_main
void	start_push_swap(t_list **stack_a, t_list **stack_b, t_count *count);
#endif