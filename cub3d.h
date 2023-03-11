#ifndef CUB3D
# define CUB3D


# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "mlx/mlx.h"
# define PI 3.141592653589793238462643383279502
# define P2 PI/2
# define P3 3*PI/2
# define cube_size 32
# define size_h 540
# define DR 0.0174533 / 16


typedef struct image
{

    void *img;
    void *addr;

    int bits_per_pixel;
    int line_length;
    int endian;



}t_image;

typedef struct ray_cast 
{
    double h_rx;
    double h_ry;
    double h_ra;
    double h_xo;
    double h_yo;
    double h_dist;
    double aTan;



    double v_rx;
    double v_ry;
    double v_ra;
    double v_xo;
    double v_yo;
    double v_dist;
    double nTan;

    double r_dist;
    char wall_dir;
    int rx;
    int ry;
} t_rt;

typedef struct cub3d 
{
    char **p_cub;
    char **map;

    char pos_j;

    char *NO;
    char *SO;
    char *WE;
    char *EA;

    int px;
    int py;



    double pdx_1;
    double pdy_1;
    double pa;

    double pdx_2;
    double pdy_2;

    int *F;
    int *C;

    void	*mlx;
    void	*mlx_win;

    t_rt    rt;

    t_image *data_im;
    t_image *wall_im;

    int i_rays;
    int rays[960];
    int rays_col[960];


    int old_x;
    int old_y;
    int old_dir;



    int nb_cube;
    int x_desc[960];  //[0,0,0,1,1,2,2,2,2,3,3,3,3,3,3]



} t_cub3d;





// outils
int	ft_strcmp(char *s1, char *s2);
int ft_strlen(char *str);
int		ft_atoi(const char *str);
char		*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char **ft_split(char *str);
char		**ft_split_simple(char *s, char c);
int ft_tablen(char **tab);



// parsing
char **ft_malloc_cub(int n, char *buf);
char  **ft_read_cub(t_cub3d *data);
void ft_init_var(t_cub3d *data);
int *ft_path_fc(char *str);
char *ft_path(char *str);
int ft_verif_ex_0(t_cub3d *data, char **line);
int ft_verif_ex(t_cub3d *data, char **line);
int ft_verif_para(t_cub3d *data);
void ft_creat_map(t_cub3d *data, int j, int i);
int ft_v_SOEAWENO(t_cub3d *data);
int ft_search_p_j(t_cub3d *data);
int ft_verif_map(t_cub3d *data);
int ft_parcing(t_cub3d *data);
int ft_manage_pj(t_cub3d *data);

//free
void ft_free_all(t_cub3d *data);
void free_double_tab(char **tab);


//mini map

void draw_case(t_cub3d *data , int x_pos , int y_pos , int col);
void draw_mini_map(t_cub3d *data);
int get_width(char **map);
int get_length(char **map);
void int_pos_player(t_cub3d *data);
void draw_player(t_cub3d *data);
void   draw_view_line(t_cub3d *data);
void   draw_line(t_cub3d *data , double angle);
void draw_vision(t_cub3d *data , t_rt *rt);



// rc 
void   calcul_h_dist(t_cub3d *data, t_rt *rt,double angle);
void   calcul_v_dist(t_cub3d *data, t_rt *rt,double angle);
void draw_rc(t_cub3d *data, double r_dist , int line_pos, double angle);




int	move_player(int key, t_cub3d *data);
double dist(double ax,double ay, double bx, double by, double ang);
void int_delta(t_cub3d *data);
void display(t_cub3d *data);

#endif