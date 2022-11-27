/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:44:30 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/27 20:36:17 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_make_remain(char *temp)
{
	int		i;
	int		j;
	int		len;
	char	*remain;

	i = 0;
	j = -1;
	len = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	while (temp[i + len])
		len++;
	if (len == 0)
	{
		free(temp);
		return (0);
	}
	remain = (char *)malloc(sizeof(char) * (len + 1));
	while (++j < len)
		remain[j] = temp[i + j];
	remain[j] = 0;
	free(temp);
	return (remain);
}

char	*ft_make_line(char *temp)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	j = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	new_line = (char *)malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		new_line[j] = temp[j];
		j++;
	}
	new_line[j] = 0;
	return (new_line);
}

char	*ft_get_line(int fd, char *temp)
{
	char	*buff;
	int		read_status;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (1)
	{
		read_status = read(fd, buff, BUFFER_SIZE);
		buff[BUFFER_SIZE] = 0;
		if (read_status == BUFFER_SIZE && find_nl(buff) == 0)
			temp = ft_strjoin(temp, buff);
		else if (read_status == -1 || ((!temp) && read_status == 0))
		{
			if (temp)
				free (temp);
			free(buff);
			return (0);
		}
		else
			break ;
	}
	if (read_status != BUFFER_SIZE)
		buff[read_status] = 0;
	temp = ft_strjoin(temp, buff);
	free(buff);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;

	if (find_nl(temp) == 0)
		temp = ft_get_line(fd, temp);
	if (!temp || temp[0] == 0)
	{
		free(temp);
		return (0);
	}
	line = ft_make_line(temp);
	temp = ft_make_remain(temp);
	return (line);
}

/*
int	main(void)
{
	int		fd;
	char	*line;

	if (0 < (fd = open("./test.txt", O_RDONLY)))
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	else
	{
		printf("파일 열기에 실패했습니다.\n");
	}
	return (0);
}*/