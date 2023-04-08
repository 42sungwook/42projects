#include "pipex.h"


// t_list	*pid_addlist(pid_t pid)
// {
// 	t_list	*list;

// 	list = (t_list *)malloc(sizeof(t_list));
//     list->pid = pid;
// 	list->next = 0;
// 	return (list);
// }

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}
char *join_path(char *path, char *cmd)
{
    size_t i, j, path_len, cmd_len;
    char *join;

    path_len = ft_strlen(path);
    cmd_len = ft_strlen(cmd);
    join = (char *)malloc(sizeof(char) * (path_len + cmd_len + 2));
    if (!join)
        return (0);
    i = 0;
    while (i < path_len)
    {
        join[i] = path[i];
        i++;
    }
    join[i] = '/';
    i++;
    j = 0;
    while (j < cmd_len)
    {
        join[i + j] = cmd[j];
        j++;
    }
    join[i + j] = 0;
    return (join);
}

// static void handle_cmd(t_fds fds, char *cmd, char **paths, char **envp)
// {
//     char **args;
//     size_t i;

//     i = 0;
//     dup2(fds.fd3, STDIN_FILENO); // we want f1 to be execve() input
//     dup2(fds.pipe_fd[1], STDOUT_FILENO); // we want end[1] to be execve() stdout
//     close(fds.pipe_fd[0]);
//     close(fds.fd3);
//     while (paths[i])
//     {
//         args = (char **)malloc(sizeof(char *) * 3);
//         if (!args)
//             exit(1); // handle allocation error
//         args[0] = join_path(paths[i], cmd);
//         args[1] = cmd;
//         args[2] = NULL;
//         execve(args[0], args, envp);
//         free(args[0]);
//         free(args);
//         i++;
//     }
//     perror("Error"); // handle execve error
//     exit(1);
// }

// int child_process(t_fds fds, char **argv, char **paths, t_list **pids, char **envp)
// {
//     pid_t   child;
//     t_list  *temp;
//     size_t  i;
//     int     status;
//     char    **args;

//     i = 2;
//     while (argv[i + 1])
//     {
//         child = fork();
//         if (child == -1)
//             perror("Fork");
//         if (!(*pids))
//         {
//             *pids = pid_addlist(child);
//             temp = *pids;
//         }
//         else
//         {
//             temp->next = pid_addlist(child);
//             temp = temp->next;
//         }
//         if (child == 0)
//             handle_cmd(fds, argv[i], paths, envp);
//         i++;
//     }
//     temp = *pids;
//     while (temp)
//     {
//         waitpid(temp->pid, &status, 0);
//         temp = temp->next;
//     }
//     dup2(fds.fd4, STDOUT_FILENO);
//     dup2(fds.pipe_fd[0], STDOUT_FILENO);
//     close(fds.pipe_fd[1]);
//     close(fds.fd4);
//     i = 0;
//     while (paths[i])
//     {
//         args = (char **)malloc(sizeof(char *) * 3);
//         if (!args)
//             exit(1);
//         args[0] = join_path(paths[i], argv[1]);
//         args[1] = argv[3];
//         args[2] = NULL;
//         execve(args[0], args, envp);
//         free(args[0]);
//         free(args);
//         i++;
//     }
//     perror("Error");
//     exit(1);
// }
