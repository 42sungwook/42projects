/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:34 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/16 20:41:24 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_commands *cmds)
{
	char	*path;
	char	*buf;

	buf = 0;
	path = getcwd(buf, 0);
	if (!cmds->fds->outfile)
		cmds->fds->outfile = 1;
	write(cmds->fds->outfile, path, ft_strlen(path));
	write(cmds->fds->outfile, "\n", 1);
	return (0);
}
