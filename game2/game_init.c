/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:49:41 by aclakhda          #+#    #+#             */
/*   Updated: 2025/03/06 21:18:53 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char map[WINDOW_HEIGHT][WINDOW_WIDTH] = { //tmp!!
	"1111111111",
	"1000010011",
	"1000010001",
	"1000010001",
	"1110011101",
	"1000000001",
	"1000000001",
	"1101000001",
	"1001000011",
	"1111111111"
};

float	degree_to_radian(float degree)
{
	return (degree * (PI / 180));
}

float	draw_line(t_data *img, int x0, int y0, int x1, int y1, int color) //tfrj l algho dyal Bresenham's
{
	int dx;
	int dy;
	int p;
	int x;
	int y;
	int x_step;
	int y_step;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	x_step = (x1 >= x0) ? 1 : -1;
	y_step = (y1 >= y0) ? 1 : -1;

	x = x0;
	y = y0;

	if (dx > dy)
	{
		p = 2 * dy - dx;
		for (int i = 0; i <= dx; i++)
		{
			if (map[y / (16)][x / (16)] == '1')
				return sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
			my_mlx_pixel_put(img, x, y, color);
			if (p >= 0)
			{
				y += y_step;
				p -= 2 * dx;
			}
			p += 2 * dy;
			x += x_step;
		}
	}
	else
	{
		p = 2 * dx - dy;
		for (int i = 0; i <= dy; i++)
		{
			if (map[y / (16)][x / (16)] == '1')
				return sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
			my_mlx_pixel_put(img, x, y, color);
			if (p >= 0)
			{
				x += x_step;
				p -= 2 * dy;
			}
			p += 2 * dx;
			y += y_step;
		}
	}
	return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));//distance between two points googliha ila nsiti
}

void	init_player(t_player *player)
{
	player->x = 164;
	player->y = 164;
	player->dir = 180;
}

void	init_camera(t_camera *cam)
{
	cam->x = 164;
	cam->y = 164;
	cam->dirX = cos(degree_to_radian(180));
	cam->dirY = sin(degree_to_radian(180));
	cam->planeX = -cam->dirY * tan(degree_to_radian(FOV/ 2));
	cam->planeY = cam->dirX * tan(degree_to_radian(FOV/ 2));
}

void	game(t_data *img)
{
	void	*mlx;
	void	*win;

	void	*bocchi;
	t_player	player;
	t_window	window;

	init_camera(&window.camera);
	init_player(&player);
	mlx = mlx_init(); //check if it need clear
	win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "ULTRAKILL"); //clear window
	img.img = mlx_new_image(mlx, 1920, 1080); // clear img
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian); //clear img
	gettimeofday(&window.last_time, NULL);//remove this
	window.mlx = mlx;
	window.player = player;
	window.win = win;
	window.img = img;
	window.mov = (t_move){0, 0, 0, 0, 0};
	draw_scene(&img, &window);
	mlx_hook(win, 2, 1L<<0, key_press, &window);//for pressing keys
	mlx_hook(win, 3, 1L<<1, key_release, &window);//for releasing keys
	mlx_loop_hook(mlx, update_player, &window);//for redrawing player if he moved eash frame
	mlx_loop(mlx);
	//free here
}
