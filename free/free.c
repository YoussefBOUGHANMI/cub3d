
#include"../cub3d.h"

void free_double_tab(char **tab)
{
    int i = 0;
    while (tab[i])
	{
        free(tab[i]);
        i++;
    }
    free(tab);
}

void ft_free_all(t_cub3d *data)
{
    // if (data->p_cub != NULL)
    //     free_double_tab(data->p_cub);
    if (data->map != NULL)
        free_double_tab(data->map);
    if (data->NO != NULL)
        free(data->NO);
    if (data->SO != NULL)
        free(data->SO);
    if (data->WE != NULL)
        free(data->WE);
    if (data->EA != NULL)
        free(data->EA);
    if (data->F != NULL)
        free(data->F);
    if (data->C != NULL)
        free(data->C);
}
