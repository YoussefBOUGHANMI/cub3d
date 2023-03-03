#ifndef CUB3D
# define CUB3D


# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "mlx/mlx.h"
# define PI 3.14159265359
# define P2 PI/2
# define P3 3*PI/2
# define cube_size 32
# define DR 0.0174533 / 8

typedef struct ray_cast 
{
    float h_rx;
    float h_ry;
    float h_ra;
    float h_xo;
    float h_yo;
    float h_dist;
    float aTan;



    float v_rx;
    float v_ry;
    float v_ra;
    float v_xo;
    float v_yo;
    float v_dist;
    float nTan;

    float r_dist;
    char wall_dir;

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



    float pdx_1;
    float pdy_1;
    float pa;

    float pdx_2;
    float pdy_2;

    int *F;
    int *C;

    void	*mlx;
    void	*mlx_win;

    t_rt    rt;
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
void   draw_line(t_cub3d *data , float angle);
void draw_vision(t_cub3d *data , t_rt *rt);



// rc 
float   calcul_h_dist(t_cub3d *data, t_rt *rt,float angle);
float   calcul_v_dist(t_cub3d *data, t_rt *rt,float angle);
void draw_rc(t_cub3d *data, float r_dist , int line_pos, float angle);




int	move_player(int key, t_cub3d *data);
float dist(float ax,float ay, float bx, float by, float ang);
void int_delta(t_cub3d *data);
float   calcul_h_dist(t_cub3d *data, t_rt *rt,float angle);

#endif