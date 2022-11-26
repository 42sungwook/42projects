#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 3

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*new_str;

	i = 0;
	len = 0;
	while (s1[len] != '\n')
		len++;
	new_str = (char *)malloc(sizeof(char) * (len + 2));
	while(i < len + 2)
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

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

char	*make_remain(char *buff)
{
	size_t	i;
	size_t	j;
	char	*remain;

	i = 0;
	j = 0;
	while (buff[i] != '\n')
		i++;
	remain = (char *)malloc(sizeof(char) * (BUFFER_SIZE - i + 1));
	while(j < BUFFER_SIZE - i)
	{
		remain[j] = buff[j];
		j++;
	}
	remain[j] = 0;
	return (remain);
}

char	*make_line(t_list *start)
{
	size_t	i;
	char	*line;

	i = 0;
	while (start->next != 0)
	{
		if (find_nl(start->content) > 0)
		{
			if (!line)
				line = ft_strdup(start->content);
			return (line);
		}
		else
		{
			if (!line)
				line = 0;
			line = ft_strjoin(line, start->content);
			start = start->next;
		}
	}
	line = ft_strjoin(line, start->content);
	return (line);	
}

int	ft_read(int fd, t_list	*buff)
{
	int	read_status;
	char	*content;

	content = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	read_status = read(fd, buff->content, BUFFER_SIZE);	
	content[BUFFER_SIZE] = 0;
	buff->content = content;
	return (read_status);
}

char	*get_next_line(int fd)
{
	t_list		*start;
	t_list		*buff_line;
	char		*line;
	static char	*remain;

	if (ft_read(fd, start) <= 0) //읽을 때 에러 혹은 읽을게 없을 경우
		return (0);
	start->next = 0;
	if (find_nl(start->content) != 0)		//개행문자를 찾으면
	{
		line = make_line(start);
		remain = make_remain(start->content);
		return (line);
	}
	start->next = buff_line;
	while (ft_read(fd, buff_line) > 0)
	{
		buff_line->next = 0;
		if (find_nl(buff_line->content) != 0)	//개행문자를 못 찾으면
			buff_line = buff_line->next;
		else								// 개행문자를 찾으면
		{
			line = make_line(start);
			remain = make_remain(buff_line->content);
			return (line);
		}
	}
	buff_line->next = 0;
	line = make_line(start);
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
	}
	else
	{
		printf("파일 열기에 실패했습니다.\n");
	}
	return (0);
}
