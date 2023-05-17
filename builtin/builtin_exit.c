/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:33:44 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/17 19:53:00 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_exit_ll(char *str)
{
	long long	result;
	long long	temp;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	if (!ft_strcmp(str, "-9223372036854775808"))
		return ;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		str++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = result * 10 + (str[i++] - ASCII_ZERO);
		if (temp < result)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(-1);
		}
		result = temp;
	}
}

void	print_not_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(-1);
		}
	}
}

int	builtin_exit(t_commands *cmds)
{
	char	*str;
	int		status;

	status = 0;
	if (cmds->cmd[1] && cmds->cmd[2])
	{
		str = cmds->cmd[1];
		parse_exit_ll(str);
		print_not_digit(str);
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (cmds->cmd[1])
	{
		str = cmds->cmd[1];
		parse_exit_ll(str);
		print_not_digit(str);
		status = ft_atoi(str);
		ft_putstr_fd("exit\n", 2);
		exit(status);
	}
	ft_putstr_fd("exit\n", 2);
	exit(g_exit_status);
	return (0);
}
