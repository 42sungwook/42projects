/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:52 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/28 15:10:29 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_pipex(int temp_fd)
{
	char	*line;

	line = readline("heredoc> ");
	while (line)
	{
		if (!line)
			break ;
		write(temp_fd, line, ft_strlen(line));
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(temp_fd);
}
