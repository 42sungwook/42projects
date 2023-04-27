/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:34 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/27 15:59:35 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_commands *cmd)
{
	char	*path;
	char	*buf;

	path = getcwd(buf, 0);
	return (write(1, path, ft_strlen(path)));
}
