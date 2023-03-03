
#include"../cub3d.h"

int ft_search_p_j2(t_cub3d *data, int i, int j)
{
    if (data->pos_j != 0)
        return(-1);
    if (data->map[i-1][j] != '1' && data->map[i-1][j] != '0')
        return(-3);
    if (data->map[i+1][j] != '1' && data->map[i+1][j] != '0')
        return(-3);
    if (data->map[i][j-1] != '1' && data->map[i][j-1] != '0')
        return(-3);
    if (data->map[i][j+1] != '1' && data->map[i][j+1] != '0')
        return(-3);
    return(1);
}

int ft_search_p_j(t_cub3d *data)
{
    int i;
    int j;

    i = 0;
    while(data->map[i])
    {
        j = 0;
        while(data->map[i][j])
        {
            if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W')
            {
                if (ft_search_p_j2(data, i, j) < 0)
                    return(ft_search_p_j2(data, i, j));
                data->pos_j = data->map[i][j];
            }
            j++;
        }
        i++;
    }
    if ((i < 2))
        return(-2);
    if (data->pos_j == 0)
        return(-4);
    return(1);
}

int ft_manage_pj(t_cub3d *data)
{
    int a;

    a = ft_search_p_j(data);
    if (a < 0)
    {
        if (a == -1)
            printf("Error parsing : Double position joueur\n");
        if (a == -2)
            printf("Error parsing : Map error or double map\n");
        if (a == -3)
            printf("Error parsing : Joueur hors zone\n");
        if (a == -4)
            printf("Error parsing : Position joueur manquant\n");
        return(-1);
    }
    return(a);
}
