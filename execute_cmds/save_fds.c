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

	temp = cmds->infile;
	while (temp)
	{
		if (cmds->fds->infile)
			close(cmds->fds->infile);
		cmds->fds->infile = open(temp->line, O_RDONLY);
		temp = temp->next;
	}
}

void	open_outfile_list(t_commands *cmds)
{
	t_line		*temp;

	temp = cmds->outfile;
	while (temp)
	{
		if (cmds->fds->outfile)
			close(cmds->fds->outfile);
		cmds->fds->outfile = open(temp->line, O_WRONLY);
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
