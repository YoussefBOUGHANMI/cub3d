#include"cub3d.h"



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

int main()
{
    int col;
    void	*mlx;
    void	*mlx_win;
    int color = create_trgb(0,0, 255);

	int		img_width;
	int		img_height;
	void	*img;


    t_image *data_im = malloc(sizeof(t_image));
    t_image *wall_im = malloc(sizeof(t_image));

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 500, 360, "cub3d");

    data_im->img = mlx_new_image(mlx, 300, 300);
    data_im->addr = mlx_get_data_addr(data_im->img, &data_im->bits_per_pixel, &data_im->line_length, &data_im->endian);

    wall_im->img =mlx_xpm_file_to_image(mlx, "wall.xpm", &img_width, &img_height);
    wall_im->addr = mlx_get_data_addr(wall_im->img, &wall_im->bits_per_pixel, &wall_im->line_length, &wall_im->endian);



    int i = 0;
    int ii = 0;
    while(i<64)
    {
        ii =0;
        while(ii<64)
        {
                col = get_pixel_col(wall_im, i, ii);
                my_mlx_pixel_put(data_im, i, ii , col);
                ii++;
        }
        i++;
    }


	mlx_put_image_to_window(mlx, mlx_win, data_im->img, 2, 2);
    mlx_loop(mlx);
}

