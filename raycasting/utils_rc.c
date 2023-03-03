#include"../cub3d.h"



float dist(float ax,float ay, float bx, float by, float ang)
{
    return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}


void int_delta(t_cub3d *data)
{
    float angle;

    data->pa = 0;
    data->pdx_1 = cos(data->pa) * 12;
    data->pdy_1 = sin(data->pa) * 12;


    angle = data->pa - P2;
    if(angle <0)
        angle += 2*PI;
    data->pdx_2 = cos(angle) * 12;
    data->pdy_2= sin(angle) * 12;
}