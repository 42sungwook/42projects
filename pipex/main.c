/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:11:07 by sungwook          #+#    #+#             */
/*   Updated: 2023/04/15 16:19:44 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	**path;

	i = 1;
	path = save_paths(args->envp);
	while (args->argv[++i + 1])
	{
		j = check_access_and_save(args, path, i);
		if (!path[j] || args->argv[i][0] == 0)
			save_no_path(args, i);
	}
	free_arr(path);
}

void	open_files(t_arguments *args)
{
	int		infile_fd;
	int		outfile_fd;
	size_t	i;

	args->fds = (t_fds *)malloc(sizeof(t_fds));
	infile_fd = open(args->argv[1], O_RDONLY);
	i = 4;
	while (args->argv[i + 1])
		i++;
	outfile_fd = open(args->argv[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	args->fds->infile = infile_fd;
	args->fds->outfile = outfile_fd;
	args->fds->infile_name = args->argv[1];
	args->fds->outfile_name = args->argv[i];
}

int	main(int argc, char **argv, char **envp)
{
	t_arguments	*args;

	if (argc != 5)
		return (0);
	args = init_args(argc, argv, envp);
	open_files(args);
	if (args->fds->infile < 0)
		perror(argv[1]);
	save_cmds(args);
	pipex(args);
	exit (0);
}
