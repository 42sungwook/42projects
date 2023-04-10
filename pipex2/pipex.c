#include "pipex.h"

//./pipex infile "ls -l" "wc -l" outfile
//< infile ls - l | wc -l > outfile

//char *args[] = {fullpath, filename, NULL};
// int ret = execve(args[0], args, envp);

static int check_path_line(char *str, char *word)
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

t_fds   open_files(char **argv)
{
    int     infile_fd;
    int     outfile_fd;
    t_fds   fds;
    size_t  i;

    infile_fd = open(argv[1], O_RDONLY);
    i = 4;
    while (argv[i + 1])
        i++;
    outfile_fd = open(argv[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
    fds.infile = infile_fd;
    fds.outfile = outfile_fd;
    fds.infile_name = argv[1];
    fds.outfile_name = argv[i];
    return (fds);
}


void    pipex (t_fds fds, t_arguments args, char **paths)
{
    size_t  i;

    i = 0;
    make_pipe(fds.curr_pipe);
    while (i < args.argc - 2)
    {
        fork_process(fds, args, paths, i);
        i++;
    }
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