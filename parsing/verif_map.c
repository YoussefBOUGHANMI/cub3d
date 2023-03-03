
#include"../cub3d.h"


int ft_v_lpd(t_cub3d *data, int i)
{
    int j;

    j = 0;
    while(data->map[i][j])
    {
        if (data->map[i][j] != ' ' && data->map[i][j] != '1')
            return(-1);
        j++;
    }
    return(1);
}

int ft_v_hall(t_cub3d *data, int i)
{
    int j;

    j = 0;
    while(data->map[i][j])
    {
        if ((data->map[i][j] != ' ' && data->map[i][j] != '1' && data->map[i][j] != '0' && data->map[i][j] != data->pos_j) && data->map[i][j])
            return(-3);
        if (data->map[i][j] == '0')
        {
            if (data->map[i-1][j] != '1' && data->map[i-1][j] != '0'
                && data->map[i-1][j] != data->pos_j)
                return(-2);
            if (data->map[i+1][j] != '1' && data->map[i+1][j] != '0'
                && data->map[i+1][j] != data->pos_j)
                return(-2);
            if (data->map[i][j-1] != '1' && data->map[i][j-1] != '0'
                && data->map[i][j-1] != data->pos_j)
                return(-2);
            if (data->map[i][j+1] != '1' && data->map[i][j+1] != '0'
                && data->map[i][j+1] != data->pos_j)
                return(-2);
        }
        j++;
    }
    return(1);
}

int ft_verif_map(t_cub3d *data)
{
    int i;
    int a;

    if ((ft_v_lpd(data, ft_tablen(data->map)-1) == -1)
        || (ft_v_lpd(data, 0) == -1))
    {
        printf("Error parsing : first or end line\n");
        return(-1);
    }
    if (ft_manage_pj(data) < 0)
        return(-1);
    i = 0;
    while(data->map[i])
    {
        a = ft_v_hall(data, i);
        if (a < 0)
        {
            if(a == -2)
                printf("Error parsing : Map ouverte\n");
            if(a == -3)
                printf("Error parsing : Caractere inexistant\n");     
            return(-1);
        }
        i++;
    }
    return(1);
}
