
#include"../cub3d.h"



int ft_parcing(t_cub3d *data)
{
    data->p_cub = ft_read_cub(data);

    if(ft_v_SOEAWENO(data) == -1)
        return(-1);

    if(ft_verif_map(data) == -1)
        return(-1);



    return(1);
}
