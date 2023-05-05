/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:34 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 16:11:16 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(void)
{
	char	*path;
	char	*buf;

	buf = 0;
	path = getcwd(buf, 0);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	return (0);
}
