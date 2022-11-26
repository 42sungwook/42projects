#include "get_next_line.h"

size_t	find_nl(char *buff)
{
	size_t	i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*reset_char(char *s)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

size_t	ft_strlen(char	*s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	len;
	char	*new_str;

	i = 0;
	len = ft_strlen(s1);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

char	*ft_strjoin(char *buff, char *temp)
{
	char	*join;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(buff) + ft_strlen(temp);
	join = (char *)malloc(sizeof(char) * (len + 1));
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

char	*make_line(char *temp)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	j = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] != 0)
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

char	*read_make_temp(int fd, char *buff, char *temp, int sign)
{
	char	*line;
	int		read_status;

	line = (char *)malloc(sizeof(char));
	line[0] = 0;
	while (read > 0)
	{
		read_status = read(fd, buff, BUFFER_SIZE);
		if (read_status == -1)
			return (0);
		if (sign == 1)
			temp = line;
		if (!temp)
			free(line);
		line = ft_strjoin(buff, temp);
		if (find_nl(buff) > 0)
			return (line);
		reset_char(buff);
		sign = 1;
		if (read_status == 0)
			return (line);
	}
	temp = line;
	line = ft_strjoin(buff, temp);
	return (line);
}

char	*make_remain(char *line, char *temp)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*remain;

	i = 0;
	j = 0;
	len = 0;
	while (line[i])
		i++;
	while (temp[i + len])
		len++;
	remain = (char *)malloc(sizeof(char) * (len + 1));
	while (j < len)
	{
		remain[j] = temp[i + j];
		j++;
	}
	remain[j] = 0;
	return (remain);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*temp;
	char		*line;
	static char	*remain;
	int			sign;

	sign = 0;
	temp = malloc(sizeof(char));
	temp[0] = 0;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (ft_strlen(remain) != 0)
	{
		temp = remain;
		if (find_nl(remain) > 0)
			sign = 1;
		else
			temp = read_make_temp(fd, buff, temp, 0);
	}
	if (sign == 0)
		temp = read_make_temp(fd, buff, temp, 1);
	line = make_line(temp);
	remain = make_remain(line, temp);
	free(buff);
	free(temp);
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
		line = get_next_line(fd);
		printf("%s", line);
	}
	else
	{
		printf("파일 열기에 실패했습니다.\n");
	}
	return (0);
}
