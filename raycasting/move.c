#include"../cub3d.h"


int check_case(int x, int y , t_cub3d *data)
{
    if(data->map[((int)y>>5)<<5 / 32][((int)x>>5)<<5 / 32] == '1')
        return(0);
    return(1);
}


void move_cam_left(t_cub3d *data)
{
    float angle;

    data->pa -= 0.25;
    if(data->pa <0)
        data->pa += 2*PI;
    data->pdx_1 = cos(data->pa) * 12;
    data->pdy_1= sin(data->pa) * 12;

    angle = data->pa - P2;
    if(angle <0)
        angle += 2*PI;
    data->pdx_2 = cos(angle) * 12;
    data->pdy_2= sin(angle) * 12;

}

void move_cam_right(t_cub3d *data)
{
    float angle;

    data->pa += 0.25;
    if(data->pa > 2 * PI)
        data->pa -= 2*PI;
    data->pdx_1 = cos(data->pa) * 12;
    data->pdy_1 = sin(data->pa) * 12;

    angle = data->pa - P2;
    if(angle <0)
        angle += 2*PI;
    data->pdx_2 = cos(angle) * 12;
    data->pdy_2 = sin(angle) * 12;
}


void move_player_straight(t_cub3d *data)
{
    if(check_case(data->px + floor(data->pdx_1) , data->py + floor(data->pdy_1) , data) == 0)
        return;
    data->px = data->px + floor(data->pdx_1);
    data->py = data->py + floor(data->pdy_1);
}

void move_player_back(t_cub3d *data)
{
    if(check_case(data->px - floor(data->pdx_1) , data->py - floor(data->pdy_1), data) == 0)
        return;
    data->px = data->px - floor(data->pdx_1);
    data->py = data->py - floor(data->pdy_1);
}


void move_player_left(t_cub3d *data)
{
    if(check_case(data->px + floor(data->pdx_2) , data->py + floor(data->pdy_2), data) == 0)
        return;
    data->px = data->px + floor(data->pdx_2);
    data->py = data->py + floor(data->pdy_2);
}


void move_player_right(t_cub3d *data)
{
    if(check_case(data->px - floor(data->pdx_2) , data->py - floor(data->pdy_2), data) == 0)
        return;
    data->px = data->px - floor(data->pdx_2);
    data->py = data->py - floor(data->pdy_2);
}




int	move_player(int key, t_cub3d *data)
{

	if(key == 123)
        move_cam_left(data);
    if(key == 124)
        move_cam_right(data);
    if (key == 13)
        move_player_straight(data);
    if (key == 1)
        move_player_back(data);
   if (key == 0)
        move_player_left(data);
    if(key == 2)
        move_player_right(data);
	if (key == 53)
		exit(0);
    //draw_mini_map(data);
    //draw_player(data);
    //draw_view_line(data);
    draw_vision(data , &data->rt);
	return (0);
}