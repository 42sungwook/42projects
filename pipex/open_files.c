#include "pipex.h"

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
