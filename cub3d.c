
#include"cub3d.h"

void ft_print_tab(t_cub3d *data)
{
    int i;

    i = 0;
    while(data->map[i])
    {
        printf("%s\n", data->map[i]);
        i++;
    }
}

int ft_cube3D(t_cub3d *data)
{
    ft_init_var(data);
    if (ft_parcing(data) == -1)
    {
        ft_free_all(data);
        return(-1);
    }


    printf("%d %d %d\n", data->F[0], data->F[1], data->F[2]);
    printf("%d %d %d\n", data->C[0], data->C[1], data->C[2]);
    printf("%s\n", data->EA);
    printf("%s\n", data->SO);
    printf("%s\n", data->WE);
    printf("%s\n", data->NO);

    ft_print_tab(data);

    return(0);
}

float dist(float ax,float ay, float bx, float by, float ang)
{
    return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}

int	move_player(int key, t_cub3d *data)
{
    printf("ici %d %d \n" , (int)floor(data->px + data->pdx)>>5 , (int)floor(data->py + data->pdy)>>5);
	if(key == 0)
    {
        data->pa -= 0.25;
            if(data->pa <0)
                data->pa += 2*PI;
            data->pdx = cos(data->pa) * 12;
            data->pdy = sin(data->pa) * 12;
    }
	if (key == 13)
    {
        if( data->map[(int)floor(data->py + data->pdy - 1)>>5][(int)floor(data->px + data->pdx - 1)>>5] == '1')
            printf("colusion\n");
        else
        {
            data->px =  floor(data->px + data->pdx);
            data->py = floor(data->py + data->pdy);
        }
    }
	if (key == 2)
    {
        data->pa += 0.25;
            if(data->pa > 2 * PI)
                data->pa -= 2*PI;
            data->pdx = cos(data->pa) * 12;
            data->pdy = sin(data->pa) * 12;
    }
	if (key == 1)
    {
        if( data->map[(int)floor(data->py - data->pdy - 1)>>5][(int)floor(data->px - data->pdx -1 )>>5] == '1')
            printf("colusion\n");
        else
        {
            data->px =  floor(data->px - data->pdx);
            data->py = floor(data->py - data->pdy);
        }
    }
	if (key == 53)
		exit(0);
    draw_mini_map(data);
    draw_player(data);
    draw_view_line(data);
    draw_vision(data , &data->rt);
	return (0);
}

void int_delta(t_cub3d *data)
{
    data->pa = 0;
    data->pdx = cos(data->pa) * 12;
    data->pdy = sin(data->pa) * 12;
}



float   calcul_h_dist(t_cub3d *data, t_rt *rt,float angle)
{
    printf("start h\n");
    int top = 0;

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
        top = 1;
    }

    while(top == 0)
    {
        printf("hor %d       %d \n" , (int)rt->h_rx>>5, (int)rt->h_ry>>5);
        if((int)rt->h_rx>>5 <= 0 || (int)rt->h_ry>>5 <= 0 
                || (int)rt->h_rx>>5 >= get_width(data->map) || (int)rt->h_ry>>5 >= get_length(data->map))
            {
                if((int)rt->h_rx>>5 >= get_width(data->map))
                    rt->h_rx = get_width(data->map) * 32;
                if((int)rt->h_rx>>5 <= 0 )
                    rt->h_rx = 0;
                if((int)rt->h_ry>>5 >= get_length(data->map))
                    rt->h_ry = get_length(data->map) * 32;
                if((int)rt->h_ry>>5 <= 0 )
                    rt->h_rx = 0;
                top = 1;
            }
        else if( (data->py > rt->h_ry) && data->map[((int)rt->h_ry>>5) - 1][(int)rt->h_rx>>5] == '1' )
            {
                printf("yes 1\n");
                top = 1;
            }
        else if(data->map[(int)rt->h_ry>>5][(int)rt->h_rx>>5] == '1' )
            {
                printf("yes 2\n");
                top = 1;
            }
        else
        {
            rt->h_rx+=rt->h_xo;
            rt->h_ry+=rt->h_yo;
        }
    }
    printf("hor %d       %d \n" , (int)rt->h_rx>>5, (int)rt->h_ry>>5);
    printf("distance h = : %f\n" , dist(data->px, data->py, rt->h_rx, rt->h_ry, angle));
    printf("end h\n");
    return(dist(data->px, data->py, rt->h_rx, rt->h_ry, angle));
}






float   calcul_v_dist(t_cub3d *data, t_rt *rt,float angle)
{
    printf("start v\n");
    int top = 0;

    rt->nTan = -tan(angle);
    if(angle>P2 && angle<P3)
    { 
        rt->v_rx=(((int)data->px>>5)<<5);
        rt->v_ry=(data->px-rt->v_rx) *rt->nTan + data->py;
        rt->v_xo = -32;
        rt->v_yo = -rt->v_xo*rt->nTan;
    }
    if(angle<P2 || angle >P3)
    { 
        rt->v_rx=(((int)data->px>>5)<<5) + 32;
        rt->v_ry=(data->px-rt->v_rx) *rt->nTan + data->py;
        rt->v_xo = 32;
        rt->v_yo = -rt->v_xo*rt->nTan;
    }
    if(angle == 0 || angle == PI)
    {
        rt->v_rx = data->px * 32;
        rt->v_ry = data->py * 32;
        top = 1;
    }

    while(top == 0)
    {
        printf("ver %d       %d \n" , (int)rt->v_rx>>5, (int)rt->v_ry>>5);
        if((int)rt->v_rx>>5 <= 0 || (int)rt->v_ry>>5 <= 0 
                || (int)rt->v_rx>>5 >= get_width(data->map) || (int)rt->v_ry>>5 >= get_length(data->map))
            {
                if((int)rt->v_rx>>5 >= get_width(data->map))
                    rt->v_rx = get_width(data->map) * 32;
                if((int)rt->v_rx>>5 <= 0 )
                    rt->v_rx = 0;
                if((int)rt->v_ry>>5 >= get_length(data->map))
                    rt->v_ry = get_length(data->map) * 32;
                if((int)rt->v_ry>>5 <= 0 )
                    rt->v_rx = 0;
                top = 1;
            }
        else if((data->px > rt->v_rx) && data->map[(int)rt->v_ry>>5][((int)rt->v_rx>>5) - 1] == '1')
            {
                top = 1;
            }
        else if (data->map[(int)rt->v_ry>>5][((int)rt->v_rx>>5)] == '1')
            top = 1;
        else
        {
            rt->v_rx+=rt->v_xo;
            rt->v_ry+=rt->v_yo;
        }
    }
    printf("end v\n");
    return(dist(data->px, data->py, rt->v_rx, rt->v_ry, angle));
}







int main(int ac, char **av)
{
    t_cub3d data;

    ft_cube3D(&data);
    printf("%c\n" , data.pos_j);
    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, get_width(data.map) * cube_size + 800, 
                                  get_length(data.map) * cube_size + 500, "cub3d");
    int_pos_player(&data);
    int_delta(&data);
    draw_mini_map(&data);
    draw_player(&data);
    draw_view_line(&data);
    draw_vision(&data , &data.rt);
    mlx_hook(data.mlx_win, 2, 1L<<0 , move_player , &data);
    mlx_loop(data.mlx);
    return (0);
}
