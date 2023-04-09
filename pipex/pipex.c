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

pid_t    fork_process(t_fds fds, t_arguments args, char **paths, int num)
{
    pid_t   pid;
    char    **cmds;
    char    *path;
    size_t  i;
    t_flist *temp;
    t_flist *prev_fd;

    if (num == 0)
        temp = fds.pipe_fd;
    else
    {
        i = 0;
        while (i < num)
        {
            prev_fd = fds.pipe_fd;
            prev_fd = prev_fd->next;
            i++;
        }
        temp = prev_fd -> next;
    }
    pipe(temp->pipe);
    pid = fork();
    if (pid == 0)
    {
        i = 0;
        if (num == 0)
            dup2(fds.infile, STDIN_FILENO);
        else
            dup2(prev_fd->pipe[0], STDIN_FILENO);
        dup2(temp->pipe[1], STDOUT_FILENO);
        close(temp->pipe[0]);
        close(temp->pipe[1]);
        cmds = ft_split(args.argv[2], ' ');
        while (paths[i])
        {
            path = join_path(paths[i], cmds[0]);
            execve(path, cmds, args.envp); // 제대로 실행되면 이후 코드는 실행안됨
            free(path);
            i++;
        }
    }
    close(fds.pipe_fd->pipe[0]);
    close(fds.pipe_fd->pipe[1]);
    return (pid);
}

t_flist    *pipe_addlist()
{
    t_flist *new;
    new = (t_flist *)malloc(sizeof(t_flist));
    return (new);
}

void    make_pipe(t_fds fds)
{
    t_flist *temp;

    if (!fds.pipe_fd)
    {
        fds.pipe_fd = pipe_addlist();
        temp = fds.pipe_fd;
    }
    else
    {
        temp->next = pipe_addlist();
        temp = temp->next;
    }
}

void    pipex (t_fds fds, t_arguments args, char **paths)
{
    size_t  i;
    // while argc-3만큼 돌면서 fork. 첫번째 제외하고 이전 pipe를 들고 들어가야함
    i = 0;
    fds.pipe_fd = 0;
    while (i < args.argc - 3)
    {
        make_pipe(fds);
        fork_process(fds, args, paths, i);
        i++;
    }
    //자식 프로세스가 모두 끝난 후에 waitpid를 통해서 좀비프로세스가 생기지 않게 관리
}

int	main(int argc, char **argv, char **envp)
{
    t_fds       fds;
    t_plist     *pids;
    char        **paths;
    t_arguments args;

    pids = 0;
    if (argc < 4)
        return (0);
    fds = open_files(argv);
    if (fds.infile < 0 )
        perror("Infile");
    paths = save_paths(envp);
    args.argc = argc;
    args.argv = argv;
    args.envp = envp;
    pipex(fds, args, paths);
    ft_free(paths);

}