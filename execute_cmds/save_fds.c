#include "../minishell.h"

void	init_cmds_fds(t_commands *cmds)
{
	cmds->fds = (t_fds *)malloc(sizeof(t_fds));
	cmds->fds->infile = -1;
	cmds->fds->outfile = -1;
}

void	open_infile_list(t_commands *cmds)
{
	t_line		*temp;
	int			fd;
	int			error_fd;

	error_fd = 0;
	temp = cmds->infile;
	while (temp)
	{
		if (cmds->fds->infile)
			close(cmds->fds->infile);
		fd = open(temp->line, O_RDONLY);
		if (fd == -1)
		{
			write(2, temp->line, ft_strlen(temp->line));
			write(2, ": No such file or directory\n", 28);
			error_fd = 1;
		}
		cmds->fds->infile = fd;
		temp = temp->next;
	}
	if (error_fd)
		cmds->fds->infile = -1;
}

void	open_outfile_list(t_commands *cmds)
{
	t_line		*temp;

	temp = cmds->outfile;
	while (temp)
	{
		if (cmds->fds->outfile)
			close(cmds->fds->outfile);
		cmds->fds->outfile = open(temp->line, O_CREAT | O_RDWR | O_TRUNC, 0644);
		temp = temp->next;
	}
}

void	save_fds_in_cmds(t_commands *cmds)
{
	t_commands	*temp;

	temp = cmds;
	while (temp)
	{
		init_cmds_fds(cmds);
		open_infile_list(cmds);
		open_outfile_list(cmds);
		//open_heredoc(cmds);
		temp = temp->next;
	}
}
