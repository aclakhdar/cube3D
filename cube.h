#ifndef CUBE_H
# define CUBE_H

//window size
#define WINDOW_HEIGHT 960
#define WINDOW_WIDTH 1200
#define D_PLAN 1000 //distance from the player to the projection plane

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
#define ROT_SPEED 0.3
#define MOV_SPEED 0.4
#define LINE_LENGTH 300
#define FOV 60
#define DOV 50 // depth of veiw
#define RAY_NUM 120
#define PI 3.14

//some values
#define GAB_SIZE 4
#define COL_S 64 // columes size (walls, empty space ect)
#define VER 1 //if the line is vertical
#define HOR 0 //if the line is horizontal
#define DEGREE 0.0174533 //degree to radian

//tmp
#define MAP_WIDTH 20
#define MAP_HEIGHT 20

//debug
#define DEBUG 1
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
	char	**map;
	int			max;
	int			nb_rows;
	int			nb_cols;
	int			nb_rays;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			r_f;
	int			g_f;
	int			b_f;
	int			r_c;
	int			g_c;
	int			b_c;
	t_player	player;
	int			tilesize;
	void		*texture[4];
    int		bits_per_pixel;
    int		line_length;
    int		endian;
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
	long	dist;
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
void 	draw_square(t_data *img, int x_start, int y_start, int size, int color);
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


void	check_map_valid(char **map);
void	check_player_valid(char **map);
void	check_vide(char **map, t_game *game);
void	check_game(char **map);
void	check_vide_norm(char **map, t_game *game, int count);
#endif
