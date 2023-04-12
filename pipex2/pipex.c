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
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	i = 0;
	j = 0;
	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (str1[i])
	{
		str[j] = str1[i];
		i++;
		j++;
	}
	i = 0;
	str[j] = '/';
	j++;
	while (str2[i])
	{
		str[j] = str2[i];
		i++;
		j++;
	}
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
		perror("PATH");
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

void	save_cmds(t_arguments *args, char **envp)
{
	size_t	i;
	size_t	j;
	char	**cmds;
	char	**path;

	i = 2;
	path = save_paths(envp);
	while (args->argv[i + 1])
	{
		j = 0;
		while (path[j])
		{
			cmds = ft_split(args->argv[i], ' ');
			cmds[0] = join_path(path[j], cmds[0]);
			if (!access(cmds[0], X_OK))
			{
				make_cmdlist(args, cmds);
				break ;
			}
			//free cmds
			j++;
		}
		if (!path[j])
			perror("cmd");
		i++;
	}
}

t_fds	*open_files(char **argv)
{
	int		infile_fd;
	int		outfile_fd;
	t_fds	*fds;
	size_t	i;

	fds = (t_fds *)malloc(sizeof(t_fds));
	infile_fd = open(argv[1], O_RDONLY);
	i = 4;
	while (argv[i + 1])
		i++;
	outfile_fd = open(argv[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	fds->infile = infile_fd;
	fds->outfile = outfile_fd;
	fds->infile_name = argv[1];
	fds->outfile_name = argv[i];
	return (fds);
}

void	pipex (t_fds fds, t_arguments *args, char **envp)
{
	size_t	i;
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;
	char	**cmds;
	int		signal;

	i = 0;
	pipe(fds.pipe1);
	pid1 = fork();
	if (pid1 == 0) // 첫번째 자식 프로세스
	{
		dup2(fds.infile, STDIN_FILENO);
		dup2(fds.pipe1[1], STDOUT_FILENO);
		close(fds.infile);
		close(fds.pipe1[0]);
		close(fds.pipe1[1]);
		cmds = ft_split(args->argv[2], ' ');
		while (paths[i])
		{
			path = join_path(paths[i], cmds[0]);
			execve(path, cmds, args.envp);
			free(path);
			i++;
		}
	}
	pipe(fds.pipe2);
	pid2 = fork();
	if (pid2 == 0) // 두번째 자식 프로세스
	{
		dup2(fds.pipe1[0], STDIN_FILENO);
		dup2(fds.pipe2[1], STDOUT_FILENO);
		close(fds.pipe1[0]);
		close(fds.pipe1[1]);
		close(fds.pipe2[0]);
		close(fds.pipe2[1]);
		cmds = ft_split(args.argv[3], ' ');
		while (paths[i])
		{
			path = join_path(paths[i], cmds[0]);
			// write(2, path, ft_strlen(path));
			// write(2, "\n", 1);
			execve(path, cmds, args.envp);
			free(path);
			i++;
		}
	}
	//부모 프로세스
	close(fds.pipe1[0]);
	close(fds.pipe1[1]);
	pid3 = fork();
	if (pid3 == 0) // 세번째 자식 프로세스
	{
		dup2(fds.pipe2[0], STDIN_FILENO);
		dup2(fds.outfile, STDOUT_FILENO);
		close(fds.outfile);
		close(fds.pipe2[0]);
		close(fds.pipe2[1]);
		cmds = ft_split(args.argv[4], ' ');
		while (paths[i])
		{
			path = join_path(paths[i], cmds[0]);
			execve(path, cmds, args.envp);
			free(path);
			i++;
		}
	}
	close(fds.pipe2[0]);
	close(fds.pipe2[1]);
	i = 0;
	while (i < 3)
	{
		wait(&signal);
		i++;
	}
	// waitpid(pid1, &signal, 0);
	// waitpid(pid2, &signal, 0);
	// waitpid(pid3, &signal, 0);


t_arguments	*init_args(int argc, char **argv, char **envp)
{
	t_arguments	*args;

	args = (t_arguments *)malloc(sizeof(t_arguments));
	args->argc = argc;
	args->argv = argv;
	args->envp = envp;
	args->cmds = 0;
	args->fds = 0;
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	t_fds		fds;
    // t_plist     *pids;
    // char        **paths;
	t_arguments	*args;

	if (argc < 5)
		return (0);
	args = init_args(argc, argv, envp);
	args->fds = open_files(argv);
	if (args->fds->infile < 0 )
		perror("Infile");
	save_cmds(args, envp);
	pipex(fds, args, envp);
	ft_free(paths);
}
