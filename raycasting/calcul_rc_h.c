#include"../cub3d.h"



void calcul_angle_h(t_cub3d *data, t_rt *rt,float angle, int *top)
{
    rt->aTan = -1/tan(angle);
    if(angle>PI)
    { 
        rt->h_ry=(((int)data->py>>5)<<5);
        rt->h_rx=(data->py-rt->h_ry) *rt->aTan + data->px;
        rt->h_yo = -32;
        rt->h_xo = -rt->h_yo*rt->aTan;
    }
    if(angle<PI)
    { 
        rt->h_ry=(((int)data->py>>5)<<5) + 32;
        rt->h_rx=(data->py-rt->h_ry) *rt->aTan + data->px;
        rt->h_yo = 32;
        rt->h_xo = -rt->h_yo*rt->aTan;
    }
    if(angle == 0 || angle == PI)
    {
        rt->h_rx = data->px * 32;
        rt->h_ry = data->py * 32;
        *top = 1;
    }
}

void    calcul_h_dist_bis(t_cub3d *data, t_rt *rt,float angle, int *top)
{
    if((int)rt->h_rx>>5 >= get_width(data->map))
        rt->h_rx = get_width(data->map) * 32;
    if((int)rt->h_rx>>5 <= 0 )
        rt->h_rx = 0;
    if((int)rt->h_ry>>5 >= get_length(data->map))
        rt->h_ry = get_length(data->map) * 32;
    if((int)rt->h_ry>>5 <= 0 )
        rt->h_rx = 0;
    *top = 1;
}

float   calcul_h_dist(t_cub3d *data, t_rt *rt,float angle)
{
    int top = 0;

    calcul_angle_h(data,rt,angle,&top);
    while(top == 0)
    {
        if((int)rt->h_rx>>5 <= 0 || (int)rt->h_ry>>5 <= 0 
                || (int)rt->h_rx>>5 >= get_width(data->map) 
                || (int)rt->h_ry>>5 >= get_length(data->map))
            calcul_h_dist_bis(data,rt,angle,&top);
        else if( (data->py > rt->h_ry) && data->map[((int)rt->h_ry>>5) - 1][(int)rt->h_rx>>5] == '1' )
                top = 1;
        else if(data->map[(int)rt->h_ry>>5][(int)rt->h_rx>>5] == '1' )
                top = 1;
        else
        {
            rt->h_rx+=rt->h_xo;
            rt->h_ry+=rt->h_yo;
        }
    }
    return(dist(data->px, data->py, rt->h_rx, rt->h_ry, angle));
}

