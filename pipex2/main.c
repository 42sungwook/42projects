#include "pipex.h"

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

void	save_cmds(t_arguments *args)
{
	int		i;
	int		j;
	char	**cmd;
	char	**path;

	i = 1;
	path = save_paths(args->envp);
	while (args->argv[++i + 1])
	{
		j = -1;
		while (path[++j] && args->argv[i][0] != 0)
		{
			cmd = ft_split(args->argv[i], ' ');
			cmd[0] = join_path(path[j], cmd[0]);
			if (!access(cmd[0], X_OK))
			{
				make_cmdlist(args, cmd);
				args->cmd_count++;
				break ;
			}
			free_arr(cmd);
		}
		if (!path[j] || args->argv[i][0] == 0)
		{
			cmd = ft_split(args->argv[i], ' ');
			if (!(args->fds->infile == -1 && i + 1 == 3))
			{
				write(2, args->argv[i], ft_strlen(args->argv[i]));
				write(2, ": command not found", 19);
				write(2, "\n", 1);
			}
			make_cmdlist(args, cmd);
			args->cmd_count++;
		}
	}
	free_arr(path);
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
}

int	main(int argc, char **argv, char **envp)
{
	t_arguments	*args;

	if (argc < 5)
		return (0);
	args = init_args(argc, argv, envp);
	open_files(args, argv);
	if (args->fds->infile < 0)
		perror(argv[1]);
	save_cmds(args);
	// if (args->cmds == NULL)
	// 	return (0);
	pipex(args);
	exit (0);
}
