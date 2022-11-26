#include "get_next_line.h"

char	*make_line(char *temp, char *remain)
{
	int		i;
	int		j;
	int		count;
	char	*new_line;

	i = 0;
	j = 0;
	while (temp[i])
	{
		if (temp[i] != '\n')
			count++;
		i++;
	}
	new_line = (char *)malloc(sizeof(char) * (count + 1));
	remain = (char *)malloc(sizeof(char) * (BUFFER_SIZE - (count % BUFFER_SIZE) + 1));
	i = 0;
	while (i < count)
	{
		new_line[i] = temp[i];
		i++;
	}
	new_line[i] = 0;
	while (temp[i + j])
	{
		remain[j] = temp[i + j];
		j++;
	}
	return (new_line);
}

int	find_nl(char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*reset_buff(char *buff)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		buff[i] = 0;
		i++;
	}
	return (buff);
}

int	ft_strlen(char	*s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *buff, char *temp)
{
	char	*join;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(buff) + ft_strlen(temp);
	join = (char *)malloc(sizeof(char) * (len + 1));
	if (!join)
		return (0);
	while (temp[i])
	{
		join[i] = temp[i];
		i++;
	}
	while (buff[j])
	{
		join[i + j] = buff[j];
		j++;
	}
	join[i + j] = 0;
	return (join);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*temp;
	char		*line;
	static char	*remain;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	line = (char *)malloc(sizeof(char));
	line[0] = 0;
	if (!buff)
		return (0);
	buff[BUFFER_SIZE] = 0;
	while (read(fd, buff, BUFFER_SIZE) > 0)
	{
		temp = line;
		line = ft_strjoin(buff, temp);
		free(temp);
		if (find_nl(buff) == 1)
		{
			temp = line;
			line = make_line(temp, remain);
			free(buff);
			return (line);
		}
		reset_buff(buff);
	}
	temp = line;
	line = ft_strjoin(buff, temp);
	free(temp);
	free(buff);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	if (0 < (fd = open("./test.txt", O_RDONLY)))
	{
		line = get_next_line(fd);
		printf("%s", line);
		line = get_next_line(fd);
		printf("%s", line);
	}
	else
	{
		printf("파일 열기에 실패했습니다.\n");
	}
	return (0);
}