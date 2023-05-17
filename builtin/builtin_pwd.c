/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:34 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/17 21:02:49 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_commands *cmds, t_token *token)
{
	char	*path;
	char	*temp_str;

	path = getcwd(0, 0);
	if (!path)
	{
		temp_str = find_current_dir(token);
		write(cmds->fds->outfile, temp_str, ft_strlen(temp_str));
		write(cmds->fds->outfile, "\n", 1);
		free(temp_str);
		return (0);
	}
	if (!cmds->fds->outfile)
		cmds->fds->outfile = 1;
	write(cmds->fds->outfile, path, ft_strlen(path));
	write(cmds->fds->outfile, "\n", 1);
	free(path);
	return (0);
}
