#ifndef CUBE_H
# define CUBE_H

//window size
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280

//colors
#define BOCCHI 0xEEB8C4
#define grey 0x808080
#define NE 0xFFCDB2
#define YELLOW 0xFFFF00
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define TRANS 0x00FF0000

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
#define ROT_SPEED 0.6
#define MOV_SPEED 0.4
#define LINE_LENGTH 300
#define FOV 60
#define PI 3.14159265358979323846

//some values
#define GAB_SIZE 4

extern char map[WINDOW_HEIGHT][WINDOW_WIDTH]; //tmp!!

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <sys/time.h> //for mesuring fps

typedef struct s_move {
	int	up;
	int	down;
	int	left;
	int	right;
	int	moved;
	int	r_left;
	int	r_right;
}		t_move;

typedef struct s_data {
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
} t_data;

typedef struct s_player {
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	dir;
	double	old_x;
	double	old_y;
	double	old_dir;
	double	old_dx;
	double	old_dy;
}		t_player;

typedef struct window {
	void		*mlx;
	void		*win;
	t_data		img;
	t_move		mov;
	t_player	player;
	t_data		wall_img;
	float		dist[FOV];
	struct timeval last_time;//remove this
} t_window;

char	*ft_itoa(int n);
void	game(void);
int		key_press(int keycode, t_window *window);
int		key_release(int keycode, t_window *window);
int		update_player(t_window *window);
void	draw_scene(t_data *img, t_window *window);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
float	draw_line(t_data *img, int x0, int y0, int x1, int y1, int color);
void 	draw_square(t_data *img, int x_start, int y_start, int size, int color);
void	draw_walls(t_data *img);
float	degree_to_radian(float degree);

#endif
