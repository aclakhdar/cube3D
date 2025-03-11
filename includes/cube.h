#ifndef CUBE_H
# define CUBE_H

//window size



#define PI 3.1415926535
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 960
#define FOV 60
#define COL_S 64
#define D_PLAN ((int)(WINDOW_WIDTH / (2.0 * tan(FOV * PI / 360.0))))
#define MOV_SPEED 0.5
#define ROT_SPEED 0.3
#define DOV 50
#define HOR 0
#define VER 1
//colors
#define BOCCHI 0xEEB8C4
#define PINK 0xcd9da8
#define grey 0x808080
#define NE 0xFFCDB2
#define YELLOW 0xFFFF00
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define TRANS 0x00FF0000
#define GREY_H 0xb3b3b3
#define GREY_V 0x6d6d6d

//keycodes
#define UP 119
#define LEFT 97
#define DOWN 115
#define RIGHT 100
#define ESC 65307
#define R_ARROW 65363
#define L_ARROW 65361

//player movement
#define WALL_COLLISION 10
#define RAY_NUM 120



# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_EAST 2
# define TEX_WEST 3

//some values
#define GAB_SIZE 4
#define VER 1 //if the line is vertical
#define HOR 0 //if the line is horizontal
#define DEGREE 0.0174533 //degree to radian

//tmp
#define MAP_WIDTH 20
#define MAP_HEIGHT 20

//debug
#define DEBUG 0
# define BUFFER_SIZE 1
extern char map[WINDOW_HEIGHT][WINDOW_WIDTH]; //tmp!!

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <sys/time.h> //for mesuring fps
#include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>


typedef struct s_line {
    float x;
    float y;
    float dist;
    int type; // HOR or VER
    int hit;
} t_line;
typedef struct s_tex //texture
{
	void	*img;
	void	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_tex;

typedef struct s_camera
{
	double	x;
	double	y;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}			t_camera;

typedef struct s_move {
	int	up;
	int	down;
	int	left;
	int	right;
	int	moved;
	int	r_left;
	int	r_right;
}		t_move;


typedef struct s_player {
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	dir;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	float	rotation_angle;

}		t_player;

typedef struct s_data {
    void	*img;
    char	*addr;
	void		*mlx_ptr;
	int			texture_width;
	int			texture_height;
	char	**map;
	int			max;
	int			nb_rows;
	int			nb_cols;
	int			nb_rays;
	int			r_f;
	int			g_f;
	int			b_f;
	int			r_c;
	int			g_c;
	int			b_c;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	t_player	player;
	int			tilesize;
	void		*texture[4];
    int		bits_per_pixel;
    int		line_length;
    int		endian;
	int		dir;
	int		screen_height;
	int		wall_height;
	int		wall_top;
	int		wall_bottom;
	double	wall_x;
	int		tex_x;
	int		y;
	double tex_y;
	double	dist;
	float	degree;
	float	ray_angle;
	int color;
	t_tex	*tex;
	t_tex 	north;
	t_tex	south;
	t_tex	east;
	t_tex	west;
} t_data;

typedef struct s_game
{
	int		fd;
	char	*str;
	char	**map;
	char	**array;
	char	**array2;
	char	**map_alloc;
	char	*no;
	char	*we;
	char	*ea;
	char	*so;
	char	*f;
	char	*c;
	int		r_f;
	int		g_f;
	int		b_f;
	int		r_c;
	int		g_c;
	int		b_c;

}	t_game;


typedef struct s_ray {
	long	x;
	long	y;
	int		type;
	int		hit;
	double	dist;
}		t_ray;

typedef struct window {
	void		*mlx;
	void		*win;
	t_data		img;
	t_data		*image;
	t_move		mov;
	t_player	player;
	t_camera	camera;
	t_data		wall_img;
	t_ray		v_line[WINDOW_WIDTH];//lengh of vertical lines
	t_ray		h_line[WINDOW_WIDTH];//lenght of hori lines
	t_ray		f_line[WINDOW_WIDTH];//final lenghts of lines
	struct timeval last_time;//remove this
} t_window;

char	*ft_itoa(int n);
void	game(t_data	*img);
int		key_press(int keycode, t_window *window);
int		key_release(int keycode, t_window *window);
int		update_player(t_window *window);
void	draw_scene(t_data *img, t_window *window);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
float	draw_line(t_data *img, int x0, int y0, int x1, int y1, int color);
void	draw_walls(t_data *img);
float	degree_to_radian(float degree);



//utils
void	parsing(int ac, char **av, t_data *data);
void	check_newline(t_game *game);
char	*ft_substr(char *s, size_t start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_check(char *s);
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	**ft_split(const char *s, char c);

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);

void	check_no(char *line, t_game *game, int fd, char **str_split);
void	check_we(char *line, t_game *game, int fd, char **str_split);
void	check_ea(char *line, t_game *game, int fd, char **str_split);
void	check_so(char *line, t_game *game, int fd, char **str_split);
void	check_f(t_game *game, char **str_split);
void	check_c(t_game *game, char **str_split);
void	err_msg2(char *str);
void	err_msg(void);

void	check_no(char *line, t_game *game, int fd, char **str_split);
int	check_color(char *line, t_game *game, int index);
int	check_texture(char *line);
void	rgb_stuff(char *line, t_game *game, int index);
void	rgb_stuff_norm(char **str_split, t_game *game);
void	check_ac(int ac);

void	free_all(t_game *game);
void	map_size(t_game *game, t_data *data);
void	alloc_map(t_game *game, t_data *data);
void	read_map(char *map_name, t_game *game);
void	check_texture_color(char *line, t_game *game);

void	check_map_valid(char **map);
void	check_player_valid(char **map);
void	check_vide(char **map, t_game *game);
void	check_game(char **map);
void	check_vide_norm(char **map, t_game *game, int count);
void	load_textures(t_data *img);
void	draw_background(t_data *img, t_player *player);
void	draw_square(t_data *img, int x_start, int y_start, int color);
t_ray	horizontal_line(t_window *window, float dir, t_data *img);
int	check_wall_collision(double x, double y, t_data *img);
t_ray	vertical_line(t_window *window, float dir, t_data *img);
int get_pixel(t_tex *tex, int x, int y);
#endif

