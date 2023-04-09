#include "pipex.h"

//./pipex infile "ls -l" "wc -l" outfile
//< infile ls - l | wc -l > outfile

//char *args[] = {fullpath, filename, NULL};
// int ret = execve(args[0], args, envp);


void    ft_free(char **paths)
{
    size_t  i;

    i = 0;
    while (paths[i])
    {
        free(paths[i]);
        i++;
    }
    free(paths);
}

pid_t    fork_process(t_fds fds, char **argv, char **paths, char **envp)
{
    int     pipe_fd[2];
    pid_t   pid;
    char    **cmds;
    char    *path;
    size_t  i;
    int     status;

    pipe(pipe_fd);
    pid = fork();
    if (pid == 0)
    {
        i = 0;
        dup2(fds.infile, STDIN_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        cmds = ft_split(argv[2], ' ');
        while (paths[i])
        {
            path = join_path(paths[i], cmds[0]);
            execve(path, cmds, envp); // 이후 코드는 실행안됨
            free(path);
            i++;
        }
        i = 0;
        while(cmds[i])
        {
            free(cmds[i]);
            i++;
        }
        free(cmds);
    }
    else
    {
        close(pipe_fd[1]);
        dup2(fds.outfile, STDOUT_FILENO);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]); // close the read end of the pipe
        // waitpid(pid, &status, 0);
        cmds = ft_split(argv[3], ' ');
        i = 0;
        while (paths[i])
        {
            path = join_path(paths[i], cmds[0]);
            execve(path, cmds, envp);
            free(path);
            i++;
        }
        i = 0;
        while(cmds[i])
        {
            free(cmds[i]);
            i++;
        }
        free(cmds);
        close(fds.infile); // close the input file descriptor
        close(fds.outfile); // close the output file descriptor
    }
    return (pid);
}

void    pipex (t_fds fds, char **argv, char **paths, char **envp)
{
    fork_process(fds, argv, paths, envp);
}

int	main(int argc, char **argv, char **envp)
{
    t_fds   fds;
    t_list  *pids;
    char    **paths;

    pids = 0;
    if (argc < 4)
        return (0);
    fds = open_files(argv);
    if (fds.infile < 0 )
        perror("Infile");
    paths = save_paths(envp);
    pipex(fds, argv, paths, envp);
    ft_free(paths);

}