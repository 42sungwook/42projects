#include "pipex.h"

int parent_process(t_fds fds,t_list *pids, char **argv)
{
    int     status;
    t_list  *temp;
    char    **args;

    temp = pids;
    while (temp)
    {
        waitpid(pids, &status, 0);  // supervising the children
        temp = temp->next;
    }
    dup2(fds.fd4, STDOUT_FILENO); // f2 is the stdout
    dup2(fds.pipe_fd[0], STDOUT_FILENO); // end[0] is the stdin
    close(fds.pipe_fd[1]);
    close(fds.fd4);
    args[0] = join_path(paths[i], cmd);
    args[1] = fds.fd3;
    args[2] = NULL;
    execve(args[0], args, envp);
}
