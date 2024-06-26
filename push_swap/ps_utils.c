/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:30:06 by sungwook          #+#    #+#             */
/*   Updated: 2023/02/17 19:33:23 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*ps_addlist(int num, int group, size_t idx)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	list->num = num;
	list->idx = idx;
	list->next = 0;
	list->group = group;
	return (list);
}

static int ps_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ps_isspace(int c)
{
	unsigned char chr;

	chr = c;
	if (chr == '\t' || chr == '\n' || chr == '\v' || \
		chr == '\f' || chr == '\r' || chr == ' ')
		return (1);
	else
		return (0);
}

int	ps_atoi(char *str)
{
	size_t	i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ps_isspace(str[i]) == 1)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (ps_isdigit(str[i]) == 0)
		exit(0);
	while (ps_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
