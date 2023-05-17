/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:34 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/17 13:31:16 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_commands *cmds)
{
	char	*path;

	path = getcwd(0, 0);
	if (!cmds->fds->outfile)
		cmds->fds->outfile = 1;
	write(cmds->fds->outfile, path, ft_strlen(path));
	write(cmds->fds->outfile, "\n", 1);
	return (0);
}
