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


int main()
{

    void	*mlx;
    void	*mlx_win;
    int color = create_trgb(0,0, 255);

	char	*relative_path;
	int		img_width;
	int		img_height;
	void	*img;


    t_image *data_im = malloc(sizeof(t_image));

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 500, 360, "cub3d");

    data_im->img = mlx_new_image(mlx, 300, 300);

    data_im->addr = mlx_get_data_addr(data_im->img, &data_im->bits_per_pixel, &data_im->line_length, &data_im->endian);



    my_mlx_pixel_put(data_im, 10, 20 , color);
    my_mlx_pixel_put(data_im, 10, 21 , color);
    my_mlx_pixel_put(data_im, 10, 22 , color);
    my_mlx_pixel_put(data_im, 10, 23 , color);
    my_mlx_pixel_put(data_im, 11, 21 , color);
    my_mlx_pixel_put(data_im, 11, 22 , color);
    my_mlx_pixel_put(data_im, 11, 23 , color);




	mlx_put_image_to_window(mlx, mlx_win, data_im->img, 0, 0);
    mlx_loop(mlx);
}

