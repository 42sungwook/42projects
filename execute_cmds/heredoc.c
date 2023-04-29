/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:52:26 by sungwook          #+#    #+#             */
/*   Updated: 2023/04/29 15:40:18 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	limiter_true(char *str1, char *str2)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str1[i] && str2[i])
// 	{
// 		if (str1[i] != str2[i])
// 			return (0);
// 		i++;
// 	}
// 	if (str1[i] || str2[i])
// 		return (0);
// 	return (1);
// }

// void	write_in_heredoc(int fd, char *limiter)
// {
// 	char	*str;

// 	str = readline(fd);
// 	while (!limiter_true(str, limiter))
// 	{
// 		write(fd, str, ft_strlen(str));
// 		free(str);
// 		str = readline(fd);
// 	}
// 	free(str);
// }

// void	open_heredoc_fd(int count)
// {
// 	int		i;
// 	char	*heredoc_file;
// 	int		file_fd;

// 	i = 0;
// 	heredoc_file = ft_strdup("/tmp/heredoc_temp");
// 	while (i < count)
// 	{
// 		if (access(heredoc_file, F_OK) == 0)
// 		{
// 			file_fd = open(heredoc_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 			write_in_heredoc(file_fd, limiter);
// 		}
// 		i++;
//     }
// }

// void	open_heredoc(t_commands *cmds)
// {
// 	t_commands	*temp_cmds;

// 	temp_cmds = cmds;
// 	while (temp_cmds)
// 	{
// 		if (temp_cmds->heredoc)
// 			open_heredoc_fd(temp_cmds->heredoc);
// 	}
// }
