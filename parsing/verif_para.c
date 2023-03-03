
#include"../cub3d.h"

int ft_verif_ex_0(t_cub3d *data, char **line)
{
    if (((ft_strcmp(line[0], "NO") == 0) && (data->NO != NULL))
        || ((ft_strcmp(line[0], "SO") == 0) && (data->SO != NULL))
        || ((ft_strcmp(line[0], "WE") == 0) && (data->WE != NULL))
        || ((ft_strcmp(line[0], "EA") == 0) && (data->EA != NULL))
        || ((ft_strcmp(line[0], "C") == 0) && (data->C != NULL))
        || ((ft_strcmp(line[0], "F") == 0) && (data->F != NULL)))
    {
        printf("double %s\n", line[0]);
        return(-1);
    }
    return(1);
}

int ft_verif_ex(t_cub3d *data, char **line)
{
    if (ft_strcmp(line[0], "NO") == 0)
        data->NO = ft_path(line[1]);
    else if (ft_strcmp(line[0], "SO") == 0)
        data->SO = ft_path(line[1]);
    else if (ft_strcmp(line[0], "WE") == 0)
        data->WE = ft_path(line[1]);
    else if (ft_strcmp(line[0], "EA") == 0)
        data->EA = ft_path(line[1]);
    else if (ft_strcmp(line[0], "F") == 0)
        data->F = ft_path_fc(line[1]);
    else if (ft_strcmp(line[0], "C") == 0)
        data->C = ft_path_fc(line[1]);
    else
        return(-1);
    return(1);
}

int ft_verif_para(t_cub3d *data)
{
    int i;
    int t;
    char **line;

    t = 0;
    i = 0;
    while(data->p_cub[i])
    {
        line = ft_split(data->p_cub[i]);
        if (line[0])
        {
            if ((ft_verif_ex_0(data, line) == -1) || (ft_verif_ex(data, line) == -1))
            {
                free_double_tab(line);
                return(-1);
            }
            else
                t++;
        }
        free_double_tab(line);
        i++;
        if (t == 6)
            break;
    }
    if (t != 6 || data->C == NULL || data->F == NULL)
        return(-1);
    return(i);
}

