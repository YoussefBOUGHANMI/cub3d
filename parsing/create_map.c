
#include"../cub3d.h"

void ft_creat_map(t_cub3d *data, int j, int i)
{
    char **map;
    char *line;
    int len_map;
    int k;

    len_map = j - i;
    map = malloc(sizeof(char *)*(len_map+1));
    k = 0;
    while (data->p_cub[i] && ft_strcmp(data->p_cub[i], "") != 0)
    {
        j = 0;
        line = malloc(sizeof(char *)*(ft_strlen(data->p_cub[i])+1));
        while(data->p_cub[i][j])
        {
            line[j] = data->p_cub[i][j];
            j++;
        }
        line[j] = '\0';
        map[k] = line;
        k++;
        i++;
    }
    map[k] = 0;
    data->map = map;
}

int ft_v_SOEAWENO2(t_cub3d *data, int i)
{
    i = ft_verif_para(data);
    if(i == -1)
    {
        printf("Erreur de parsing : parametre\n");
        return(-1);
    }
    while((i < ft_tablen(data->p_cub)-1) && ft_strcmp(data->p_cub[i], "") == 0)
        i++;
    if(i >= ft_tablen(data->p_cub)-1)
    {
        printf("Error parsing : Not map\n");
        return(-1);
    }
    return(i);
}

int ft_v_SOEAWENO(t_cub3d *data)
{
    int i;
    int j;

    i = ft_v_SOEAWENO2(data, i);
    if (i == -1)
        return(-1);
    j = i;
    while (data->p_cub[i] && ft_strcmp(data->p_cub[i], "") != 0)
        i++;
    ft_creat_map(data, i, j);
    while(data->p_cub[i])
    {
        if(data->p_cub[i])
        {
            printf("Error parsing : Multi map\n");
            return(-1);
        }
        i++;
    }
    return(i);
}
