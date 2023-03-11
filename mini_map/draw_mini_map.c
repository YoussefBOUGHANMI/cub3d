#include"../cub3d.h"
               
void draw_case(t_cub3d *data , int x_pos , int y_pos , int col)
{

    int i = 0;
    int ii = 0;

    while (i < cube_size)
    {
        ii = 0;
        while(ii< cube_size)
        {
            if(ii == cube_size - 1 || i == cube_size - 1)
                mlx_pixel_put(data->mlx, data->mlx_win, x_pos + i , y_pos  + ii, 0x000000);
            else
                mlx_pixel_put(data->mlx, data->mlx_win, x_pos + i , y_pos  + ii, col);
            ii++;
        }
        i++;
    }

}

void draw_mini_map(t_cub3d *data)
{
int i = 0;
int ii = 0;

while(data->map[i])
{
    ii = 0;
    while(data->map[i][ii])
    {
        if(data->map[i][ii] == '1')
            draw_case(data , ii*cube_size , i*cube_size, 0x098D00 );
        else if(data->map[i][ii] != ' ')
            draw_case(data , ii * cube_size, i*cube_size ,  0xFFFFFF);
        ii++;
    }
    i++;
}
}

void int_pos_player(t_cub3d *data)
{
    int i;
    int ii;

    i = 0;
    while (data->map[i])
    {
        ii = 0;
        while (data->map[i][ii])
        {
            if((data->map[i][ii] == 'N') 
                || (data->map[i][ii] == 'S') 
                || (data->map[i][ii] == 'E') 
                || (data->map[i][ii] == 'W'))
            {
                data->px = ii * cube_size + cube_size / 2 ; 
                data->py = i * cube_size + cube_size / 2;
                return ;
            }
            ii++;
        } 
        i++;
    }
}


void draw_player(t_cub3d *data)
{
    int i;
    int ii;

    i = 0;
    ii = 0;
    while(i<5)
    {
        ii = 0;
        while (ii<5)
        {
             mlx_pixel_put(data->mlx, data->mlx_win, data->px - 2 + ii , data->py - 2 + i, 0xFF0404);
             ii++;
        }
        i++;
    }
    mlx_pixel_put(data->mlx, data->mlx_win, data->px , data->py, 0x0000FF);
}


void   draw_view_line(t_cub3d *data)
{
int i = 0;
int ii = 0;
int iii = 0;
int x;
int y;

x = data->px;
y = data->py;
while (i < 2)
{
    ii = 0;
    while(ii < 3)
    {
        iii = 0;
        while (iii<3)
        {
             mlx_pixel_put(data->mlx, data->mlx_win, floor(x + data->pdx_1 * 1/3) - 1 + iii , floor(y + data->pdy_1 * 1/3) - 1 + ii, 0x0000FF);
             mlx_pixel_put(data->mlx, data->mlx_win, floor(x + data->pdx_1 * 2/3) - 1 + iii , floor(y + data->pdy_1 * 2/3) - 1 + ii, 0x0000FF);
             mlx_pixel_put(data->mlx, data->mlx_win, floor(x + data->pdx_1 ) - 1 + iii , floor(y + data->pdy_1) - 1 + ii, 0x0000FF);
             iii++;
        }
        ii++;
    }
    x = floor(x + data->pdx_1 );
	y = floor(y + data->pdy_1);
    i++;
}
}


void   draw_line(t_cub3d *data , double angle)
{
int i = 0;
int x;
int y;
int pdx;
int pdy;


if(angle <0)
        angle += 2*PI;
if(angle > 2 * PI)
            angle -= 2*PI;

pdx = cos(angle) * 15;
pdy = sin(angle) * 15;




x = data->px;
y = data->py;
while (i < 150)        
{
    mlx_pixel_put(data->mlx, data->mlx_win, x , y , 0x000000);
    x = floor(x + pdx);
	y = floor(y + pdy);
    i++;
}
}

int get_wall_col(t_cub3d *data, t_rt *rt)
{
    //est
    if (rt->h_dist > rt->v_dist && data->px > rt->v_rx)
        return(0x00006A);

        //printf("p1\n");
    //ouest
    if (rt->h_dist > rt->v_dist && data->px < rt->v_rx)
        return(0x0000C4);
    //printf("p2\n");
    //nord
    if (rt->h_dist < rt->v_dist && data->py > rt->h_ry)
        return(0x6A0000);
    //printf("p3\n");
    //sud
    if (rt->h_dist < rt->v_dist && data->py < rt->h_ry)
        return(0xC40000);
    //printf("p4\n");
    return(0);
}


int create_trgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}
void    my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char    *dst;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

unsigned int    get_pixel_col(t_image *img, int x, int y)
{
    char    *dst;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    return(*(unsigned int*)dst); 
}

void add_ray(t_cub3d *data, t_rt *rt , int line_pos, double angle)
{
    double ca;
    int wall_col;
    double line_H;

    ca = data->pa - angle;
    if(rt->h_dist < rt->v_dist)
    {
        rt->r_dist = rt->h_dist;
        rt->rx = (int)rt->h_rx>>5;
        rt->ry = (int)rt->h_ry>>5;
    }
    else 
    {
        rt->r_dist = rt->v_dist;
        rt->rx = (int)rt->v_rx>>5;
        rt->ry = (int)rt->v_ry>>5;
    }
    line_H = 32 * size_h/(rt->r_dist * cos(ca));
    if(line_H>size_h)
        line_H = size_h;
    if(line_H<0)
        line_H = 0;
    data->rays[line_pos] = line_H;
    data->rays_col[line_pos] = get_wall_col(data, rt);
}






void draw_screen(t_cub3d *data)
{
int x_col;
int y_col;
int col;
int i = 0;
int ii;

while(i<960)
{
    ii = 0;
    // le plafond
    while (ii< size_h/2 - floor(data->rays[i]/2))
        {   
            my_mlx_pixel_put(data->data_im, i, ii , 0x66B2FF);
            ii++;
        }
    // le mur
    while (ii< size_h/2 + floor(data->rays[i]/2))
        {   
            //my_mlx_pixel_put(data->data_im, i, ii , data->rays_col[i]);
            //printf("%d : %f \n" ,i , floor(((ii - size_h/2 + floor(data->rays[i]/2)) /floor(data->rays[i])) * 63 ));
            col = get_pixel_col(data->wall_im, (int)data->x_desc[i],
            (int)floor(((ii - size_h/2 + floor(data->rays[i]/2)) /floor(data->rays[i])) * 63 ));

            my_mlx_pixel_put(data->data_im, i, ii , col);
            ii++;
        }
    // le sol
    while (ii < size_h)
        {   
            my_mlx_pixel_put(data->data_im, i, ii , 0x808080);
            ii++;
        }
    i++;
}
}


void    calcul_x_size(int line_pos, t_rt *rt , t_cub3d *data)
{

    if(rt->h_dist < rt->v_dist)
        data->x_desc[line_pos] = (int)floor(rt->h_rx * 2) % 64;
    else
        data->x_desc[line_pos] = (int)floor(rt->v_ry * 2) % 64;

}

void draw_vision(t_cub3d *data , t_rt *rt)
{
    double angle;
    int i;

    data->nb_cube = 0;
    angle = data->pa - DR * 480;
    i = 0;
    while (i < 480 * 2)
    {
        if(angle <= 0)
                angle += 2*PI;
        if(angle >= 2 * PI)
                angle -= 2*PI;

        calcul_h_dist(data, rt, angle);
        calcul_v_dist(data, rt, angle);
        add_ray(data , rt , i, angle);
        calcul_x_size(i , rt , data);
        angle += DR;
        i++;
    }
    draw_screen(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->data_im->img, 0, 0);
}

