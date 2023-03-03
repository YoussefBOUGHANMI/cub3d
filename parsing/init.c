
#include"../cub3d.h"

int ft_nblines_map(int n, char *buf)
{
    int i;
    int nb;

    i = 0;
    nb = 0;
    while(i < n)
    {
        if (buf[i] == '\n')
            nb++;
        i++;
    }
    return(nb);
}

int ft_nb(int n, char *buf, int i)
{
    int j = 0;
    while(buf[i] != '\n' && i < n)
    {
        i++;
        j++;
    }
    return(j);
}

char **ft_malloc_cub(int n, char *buf)
{
    char    **tab;
    char    *line;
    int     i;
    int     j;
    int     l;
    
    tab = malloc(sizeof(char *)*(ft_nblines_map(n, buf)+1));
    i = 0;
    l = 0;
    while(i < n)
    {
        line = malloc(sizeof(char) * (ft_nb(n, buf, i))+1);
        j = 0;
        while(buf[i] != '\n' && i < n)
        {
            line[j] = buf[i];
            j++;
            i++;
        }
        line[j] = '\0';
        tab[l] = line;
        l++;
        i++;
    }
    tab[l] = 0;
    return(tab);
}

char  **ft_read_cub(t_cub3d *data)
{
    int fd;
    char buf[4000];
    int n;
    int len;
    char **tab;

    fd = open("map.cub", O_RDONLY);
    if (fd == -1) 
    {
        perror("open");
        return NULL;
    }
    n = read(fd, buf, 4000);

    len = ft_nblines_map(n, buf);
    tab = ft_malloc_cub(n, buf);
    return(tab);
}

void ft_init_var(t_cub3d *data)
{
    data->map = NULL;
    data->p_cub = NULL;
    data->C = NULL;
    data->F = NULL;
    data->EA = NULL;
    data->NO = NULL;
    data->SO = NULL;
    data->WE = NULL;
    data->pos_j = 0;
}
