#include "pipex.h"

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
