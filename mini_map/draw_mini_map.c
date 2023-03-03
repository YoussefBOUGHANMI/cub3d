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


void   draw_line(t_cub3d *data , float angle)
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

int get_wall_col(t_cub3d *data)
{
    //est
    if (data->rt.wall_dir == 'v' && data->px > data->rt.v_rx)
        return(0x00006A);

        //printf("p1\n");
    //ouest
    if (data->rt.wall_dir == 'v'&& data->px < data->rt.v_rx)
        return(0x0000C4);
    //printf("p2\n");
    //nord
    if (data->rt.wall_dir == 'h' && data->py > data->rt.h_ry)
        return(0x6A0000);
    //printf("p3\n");
    //sud
    if (data->rt.wall_dir == 'h' && data->py < data->rt.h_ry)
        return(0xC40000);
    //printf("p4\n");
    return(0);
}


void draw_rc(t_cub3d *data, float r_dist , int line_pos, float angle)
{
int ii = 0;
int size_h = 360;
float ca = data->pa - angle;
float line_H  = 32 * size_h/(r_dist * cos(ca));
int wall_col;
if(ca < 0)
    ca+=2*PI;
if(ca > 2*PI)
    ca-=2*PI;
if(line_H>size_h)
    line_H = size_h;
if(line_H<0)
    line_H = 0;


wall_col = get_wall_col(data);
// le plafond
while (ii< size_h/2 - floor(line_H/2))
    {   
        mlx_pixel_put(data->mlx, data->mlx_win, 1100 + line_pos , ii , 0xFFFFFF);
        ii++;
    }
// le mur
while (ii< size_h/2 + floor(line_H/2))
    {   
        mlx_pixel_put(data->mlx, data->mlx_win, 1100 + line_pos, ii  , wall_col);
        ii++;
    }
// le sol
while (ii < size_h)
    {   
        mlx_pixel_put(data->mlx, data->mlx_win, 1100 + line_pos , ii  , 0x000000);
        ii++;
    }
}





void draw_vision(t_cub3d *data , t_rt *rt)
{
    float angle;
    int i;

    angle = data->pa - DR * 240;
    i = 0;
    while (i < 480)
    {
        if(angle < 0)
                angle += 2*PI;
        if(angle > 2 * PI)
                angle -= 2*PI;
        if (calcul_h_dist(data, rt, angle) < calcul_v_dist(data, rt, angle))
        {
            rt->wall_dir = 'h';
            rt->r_dist = calcul_h_dist(data, rt, angle);
        }
        else 
        {
            rt->wall_dir = 'v';
            rt->r_dist = calcul_v_dist(data, rt, angle);
        }
        draw_rc(data , rt->r_dist , i , angle);
        //draw_rc(data , rt->r_dist , 2*i + 1 , angle);
        //draw_line(data ,angle);
        angle += DR;
        i++;
    }
}
