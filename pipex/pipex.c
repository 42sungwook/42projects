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

void    handle_cmd(t_fds fds, char *cmd, char **paths, char **envp)
{
    char    **args;
    size_t  i;

    i = 0;
    while (paths[i])
    {
        args[0] = join_path(paths[i], cmd);
        args[1] = fds.fd3;
        args[2] = NULL;
        execve(args[0], args, envp); // if execve succeeds, it exits
        // perror("Error"); <- add perror to debug
        free(cmd); // if execve fails, we free and we try a new path
        i++;
    }
}

int parent_process(t_fds fds,t_list *pids)
{
    int status;

    close(fds.pipe_fd[0]);
    close(fds.pipe_fd[1]);
    while (pids)
    {
        waitpid(pids, &status, 0);  // supervising the children
        pids = pids->next;
    }
}

int child_process(t_fds fds, char **argv, char **paths, t_list *pids, char **envp)
{
    pid_t   child;
    size_t  i;

    i = 1;
    while (argv[i + 1])
    {
        child = fork();
        if (child < -1)
            perror("Fork : ");
        pids->next = child;
        //시작 프로세스
        if (child == 0)
            handle_cmd(fds, argv[i], paths, envp);
        //끝 프로세스
        i++;
    }
    return (0);
}

int check_path_line(char *str, char *word)
{
    size_t  i;

    i = 0;
    while (word[i])
    {
        if (word[i] != str[i])
            return (0);
        i++;
    }
    return (1);
}

t_fds   open_files(char **argv)
{
    int     infile_fd;
    int     outfile_fd;
    t_fds   files;
    size_t  i;

    infile_fd = open(argv[1], O_RDONLY);
    i = 0;
    while (argv[i + 1])
        i++;
    outfile_fd = open(argv[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
    files.fd3 = infile_fd;
    files.fd4 = outfile_fd;
    return (files);
}

char    **save_paths(char **envp)
{
    size_t  i;

    i = 0;
    while(envp[i])
    {
        if (check_path_line(envp[i], "PATH="))
            break ;
        i++;
    }
    if (!envp[i])
        perror("PATH : ");
    return (ft_split(envp[i]+5, ':'));
}

int	main(int argc, char **argv, char **envp)
{
    t_fds   fds;
    t_list  *pids;
    char    **paths;

    fds = open_files(argv);
    if (fds.fd3 < 0 || fds.fd4 < 0)
        perror("FD : ");
    paths = save_paths(envp);
    pipe(fds.pipe_fd);
    child_process(fds, argv, paths, pids, envp);
    parent_process(fds, pids);
    ft_free(paths);
}