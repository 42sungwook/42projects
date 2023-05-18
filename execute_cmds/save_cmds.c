/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:58:35 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/18 17:15:20 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_path(char *str1, char *str2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = -1;
	j = -1;
	if (!str2)
		return (str1);
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

static void	check_access_and_save(t_commands *cmds, char **path)
{
	int		i;
	char	*temp;

	i = -1;
	if (!cmds->cmd || !cmds->cmd[0])
		return ;
	while (path[++i])
	{
		temp = join_path(path[i], cmds->cmd[0]);
		if (!access(temp, X_OK) && !is_directory(temp))
		{
			free(cmds->cmd[0]);
			cmds->cmd[0] = temp;
			break ;
		}
		free(temp);
	}
}

static char	**save_paths(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (0);
	return (ft_split(envp[i] + 5, ':'));
}

void	not_builtins(char **path, t_commands *temp_cmds)
{
	if (path)
		check_access_and_save(temp_cmds, path);
	if (temp_cmds->cmd && (!temp_cmds->cmd[0] || \
		access(temp_cmds->cmd[0], X_OK) || is_directory(temp_cmds->cmd[0])))
	{
		if (is_directory(temp_cmds->cmd[0]))
		{
			g_exit_status = IS_DIR;
			write(2, "minishell: ", 11);
			write(2, temp_cmds->cmd[0], ft_strlen(temp_cmds->cmd[0]));
			write(2, ": is a directory\n", 17);
			free_arr(temp_cmds->cmd);
			temp_cmds->cmd = 0;
			return ;
		}
		g_exit_status = CMD_NOT_FOUND;
		write(2, "minishell: ", 11);
		write(2, temp_cmds->cmd[0], ft_strlen(temp_cmds->cmd[0]));
		write(2, ": command not found\n", 20);
		free_arr(temp_cmds->cmd);
		temp_cmds->cmd = 0;
	}
}

int	save_cmds(t_commands *cmds, char **envp)
{
	char		**path;
	t_commands	*temp_cmds;

	path = save_paths(envp);
	temp_cmds = cmds;
	while (temp_cmds)
	{
		if (!check_builtins(temp_cmds))
			not_builtins(path, temp_cmds);
		temp_cmds = temp_cmds->next;
	}
	if (save_fds_in_cmds(cmds))
		return (1);
	free_arr(path);
	return (0);
}
