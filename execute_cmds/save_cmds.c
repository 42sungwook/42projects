/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:58:35 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/02 16:55:00 by daijeong         ###   ########.fr       */
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
	if (!cmds->cmd)
		return ;
	while (path[++i])
	{
		temp = join_path(path[i], cmds->cmd[0]);
		if (!access(temp, X_OK))
		{
			free(cmds->cmd[0]);
			cmds->cmd[0] = temp;
			break ;
		}
		free(temp);
	}
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

static char	**save_paths(char **envp)
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

void	save_cmds(t_commands *cmds, char **envp)
{
	char		**path;
	t_commands	*temp_cmds;

	if (!cmds->cmd)
		return ;
	path = save_paths(envp);
	temp_cmds = cmds;
	while (temp_cmds)
	{
		if (!temp_cmds->cmd[0] || access(temp_cmds->cmd[0], X_OK))
		{
			write(2, "minishell: ", 11);
			write(2, temp_cmds->cmd[0], ft_strlen(temp_cmds->cmd[0]));
			write(2, ": command not found\n", 20);
			free_arr(cmds->cmd);
			temp_cmds->cmd = 0;
		}
		else
			check_access_and_save(temp_cmds, path);
		save_fds_in_cmds(temp_cmds);
		temp_cmds = temp_cmds->next;
	}
	free_arr(path);
}
