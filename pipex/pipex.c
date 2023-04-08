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

void    fork_process(t_fds fds, char *argv, char **paths, char **envp)
{
    int     pipe_fd[2];
    pid_t   pid;
    char    **cmds;
    char    *path;
    size_t  i;

    i = 0;
    pipe(pipe_fd);
    pid = fork();
    if (pid == 0)
    {
        close(STDIN_FILENO);
        dup2(fds.infile, STDIN_FILENO);
        dup2(STDOUT_FILENO, pipe_fd[0]);
        close(STDOUT_FILENO);
        close(pipe_fd[0]);
        cmds = ft_split(argv, ' ');
        while (paths[i])
        {
            path = join_path(paths[i], argv);
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
    }
    else
    {
        close(pipe_fd[1]);
        waitpid(pid, NULL, 0);
        close(pipe_fd[0]); // close the read end of the pipe
        close(STDOUT_FILENO);
        dup2(fds.outfile, STDOUT_FILENO);
        execve("/bin/head", (char *[]){"wc", NULL}, envp);
        perror("execve");
        close(fds.infile); // close the input file descriptor
        close(fds.outfile); // close the output file descriptor
    }
}

void    pipex (t_fds fds, char **argv, char **paths, char **envp)
{
    fork_process(fds, argv[2], paths, envp);
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