
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



int main(int ac, char **av)
{
    t_cub3d data;
    int		img_width;
	int		img_height;

    ft_cube3D(&data);
    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, 960, size_h, "cub3d");
    int_pos_player(&data);
    int_delta(&data);
    t_image *im = malloc(sizeof(t_image));
    t_image *wall_image = malloc(sizeof(t_image));


    data.wall_im = wall_image;
    data.wall_im->img =mlx_xpm_file_to_image(data.mlx, "wall.xpm", &img_width, &img_height);
    data.wall_im->addr = mlx_get_data_addr(data.wall_im->img, &data.wall_im->bits_per_pixel, &data.wall_im->line_length, &data.wall_im->endian);

    data.data_im = im;
    data.data_im->img = mlx_new_image(data.mlx, 960, size_h );  
    data.data_im->addr = mlx_get_data_addr(data.data_im->img, &data.data_im->bits_per_pixel,
                                             &data.data_im->line_length, &data.data_im->endian);  

    draw_mini_map(&data);
    draw_player(&data);
    draw_view_line(&data);



    //draw_vision(&data , &data.rt);
    mlx_hook(data.mlx_win, 2, 1L<<0 , move_player , &data);
    mlx_loop(data.mlx);
    return (0);
}
