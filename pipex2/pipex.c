#include "pipex.h"
#include <unistd.h>

//./pipex infile "ls -l" "wc -l" outfile
//< infile ls - l | wc -l > outfile

//char *args[] = {fullpath, filename, NULL};
// int ret = execve(args[0], args, envp);

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

void	ft_free(char **paths)
{
	size_t	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*join_path(char *str1, char *str2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = -1;
	j = -1;
	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (str1[++i])
		str[i] = str1[i];
	str[i] = '/';
	i++;
	while (str2[++j])
		str[i + j] = str2[j];
	return (str);
}

static int	check_path_line(char *str, char *word)
{
	size_t	i;

	i = 0;
	while (word[i])
	{
		if (word[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

char	**save_paths(char **envp)
{
	size_t	i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (check_path_line(envp[i], "PATH="))
			break ;
		i++;
	}
	if (!envp[i])
		perror("path");
	return (ft_split(envp[i] + 5, ':'));
}

t_list	*cmd_addlist(char **cmds)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	list->cmds = cmds;
	list->next = 0;
	return (list);
}

void	make_cmdlist(t_arguments *args, char **cmds)
{
	t_list	*temp;

	if (!(args->cmds))
	{
		temp = cmd_addlist(cmds);
		args->cmds = temp;
	}
	else
	{
		temp->next = cmd_addlist(cmds);
		temp = temp->next;
	}
}

void	save_cmds(t_arguments *args)
{
	int		i;
	int		j;
	char	**cmds;
	char	**path;

	i = 1;
	path = save_paths(args->envp);
	while (args->argv[++i + 1])
	{
		j = -1;
		while (path[++j])
		{
			cmds = ft_split(args->argv[i], ' ');
			cmds[0] = join_path(path[j], cmds[0]);
			if (!access(cmds[0], X_OK))
			{
				make_cmdlist(args, cmds);
				break ;
			}
			//free cmds
		}
		if (!path[j])
			perror("cmd");
	}
}

void	open_files(t_arguments *args, char **argv)
{
	int		infile_fd;
	int		outfile_fd;
	t_fds	*fds;
	size_t	i;

	args->fds = (t_fds *)malloc(sizeof(t_fds));
	infile_fd = open(argv[1], O_RDONLY);
	i = 4;
	while (argv[i + 1])
		i++;
	outfile_fd = open(argv[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	args->fds->infile = infile_fd;
	args->fds->outfile = outfile_fd;
	args->fds->infile_name = argv[1];
	args->fds->outfile_name = argv[i];
	args->cmd_count = i - 2;
}

int	pipex (t_fds fds, t_arguments *args)
{
	size_t	i;
	pid_t	pid;
	char	**cmds;
	int		status;
	int		temp;

	i = 0;
	pipe(fds.pipe1);
	pid = fork();
	first_child_process(fds, args, pid);
	pipe(fds.pipe2);
	while (i < args->cmd_count - 2)
	{
		pid = fork();
		//홀짝 구분필요
		nth_child_process(fds, args, pid);
		i++;
	}
	//홀짝 구분필요
	close(fds.pipe1[0]);
	close(fds.pipe1[1]);
	pid = fork();
	last_child_process(fds, args, pid);
	//홀짝 구분 필요
	close(fds.pipe2[0]);
	close(fds.pipe2[1]);
	i = 0;
	while (i < 3)
	{
		if (pid == wait(&temp))
			status = temp;
		i++;
	}
	return (status);
}

t_arguments	*init_args(int argc, char **argv, char **envp)
{
	t_arguments	*args;

	args = (t_arguments *)malloc(sizeof(t_arguments));
	args->argc = argc;
	args->argv = argv;
	args->envp = envp;
	args->cmd_count = 0;
	args->cmds = 0;
	args->fds = 0;
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	t_fds		fds;
	t_arguments	*args;
	int			status;

	if (argc < 5)
		return (0);
	args = init_args(argc, argv, envp);
	open_files(args, argv);
	if (args->fds->infile < 0)
		perror("Infile");
	save_cmds(args);
	status = pipex(fds, args);
	//free everything
	return (status);
}
