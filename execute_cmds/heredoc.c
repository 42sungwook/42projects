/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:52:26 by sungwook          #+#    #+#             */
/*   Updated: 2023/04/28 21:09:52 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*join;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)malloc(sizeof(char) * len);
	if (!join)
		return (0);
	while (i < ft_strlen(s1))
	{
		join[i] = s1[i];
		i++;
	}
	while (i + j < len - 1)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = 0;
	return (join);
}

int	pipex_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] || str2[i])
		return (0);
	return (1);
}

void	open_files_heredoc(t_arguments *args)
{
	int		outfile_fd;
	int		infile_fd;
	size_t	i;

	args->fds = (t_fds *)malloc(sizeof(t_fds));
	infile_fd = open("/tmp/pipex_temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	i = 4;
	while (args->argv[i + 1])
		i++;
	outfile_fd = open(args->argv[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	args->fds->infile = infile_fd;
	args->fds->outfile = outfile_fd;
}

void	heredoc_pipex(t_arguments *args)
{
	char	*line;

	write(1, "heredoc> ", 9);
	line = get_next_line(0);
	while (line)
	{
		if (pipex_strcmp(line, ft_strjoin(args->argv[2], "\n")))
			break ;
		write(1, "heredoc> ", 9);
		write(args->fds->infile, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(args->fds->infile);
	args->fds->infile = open("/tmp/pipex_temp", O_RDONLY);
}
