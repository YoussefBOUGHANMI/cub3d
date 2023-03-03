# include <stdio.h>
# include "mlx/mlx.h"



               
void draw_case(void	*mlx, void	*mlx_win , int x_pos , int y_pos , int col)
{

    int i = 0;
    int ii = 0;

    while (i < 8)
    {
        ii = 0;
        while(ii< 8)
        {
            mlx_pixel_put(mlx, mlx_win, x_pos + i , y_pos  + ii, col);
            ii++;
        }
        i++;
    }

}

void draw_mini_map(void	*mlx, void	*mlx_win , char **map)
{
int i = 0;
int ii = 0;

while(map[i])
{
    ii = 0;
    while(map[i][ii])
    {
        if(map[i][ii] == '1')
            draw_case(mlx, mlx_win , ii*8 , i*8, 0xFF0000);
        else
            draw_case(mlx, mlx_win , ii*8, i*8 , 0x000000);
        ii++;
    }
    i++;
}
}



int main()
{

void	*mlx;
void	*mlx_win;

mlx = mlx_init();
mlx_win = mlx_new_window(mlx, 10*8, 10*8, "cub3d");
draw_mini_map(mlx, mlx_win , map);
mlx_loop(mlx);

}