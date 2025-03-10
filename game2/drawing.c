/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:26:04 by aclakhda          #+#    #+#             */
/*   Updated: 2025/03/10 19:24:23 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)// best way to put pixel in a display (using image)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_square(t_data *img, int x_start, int y_start, int size, int color)
{
	int x, y;

	for (y = y_start; y < y_start + size; y++)
	{
		for (x = x_start; x < x_start + size; x++)
			my_mlx_pixel_put(img, x, y, color);
	}
}
// 0xa71e34 hada 3jbni
// 0x1a1415 background
void	draw_walls(t_data *img)
{

	for (int i = 0; i <= WINDOW_HEIGHT / 64; i++)
	{
		for (int j = 0; j <= WINDOW_WIDTH/64; j++)
		{
			draw_square(img, j * (64), i * (64), 64, 0xFFFFFF);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == '1')
				draw_square(img, j * (64), i * (64), 64, 0x2e2022);
		}
	}
}

// void draw_3D(t_window *window, t_data *img, int i)
// {
// 	int screen_height = WINDOW_HEIGHT;
// 	int screen_width = WINDOW_WIDTH;
// 	int wall_width = screen_width / FOV + 1;
// 	int cons = COL_S * D_PLAN;
// 	int wall_height, wall_top, wall_bottom;

// 	if (window->dist[i] == 0) // Avoid division by zero
// 		return ;
// 	wall_height = cons / window->dist[i];
// 	wall_top = (screen_height / 2) - (wall_height / 2);
// 	wall_bottom = (screen_height / 2) + (wall_height / 2);
// 	for (int y = wall_top; y < wall_bottom; y++)
// 	{
// 		for (int x = i * wall_width; x < (i + 1) * wall_width; x++)
// 		{
// 			if (y >= 0 && y < screen_height && x >= 0 && x < screen_width)
// 			{
// 				// if (window->dist[i].type == HOR)
// 					my_mlx_pixel_put(img, x, y, BOCCHI);
// 				// else
// 					// my_mlx_pixel_put(img, x, y, PINK);
// 			}
// 		}
// 	}
// }


// void	draw_player(t_window *window, t_data *img)//TODO : remake the dda algho
// {
// 	int	line_x;
// 	int	line_y;
// 	int	index;

// 	index = 0;
// 	for (int i = window->player.dir - FOV / 2; i <= window->player.dir + FOV / 2; i++)
// 	{
// 		line_x = window->player.x + (cos(degree_to_radian(i)) * LINE_LENGTH);
// 		line_y = window->player.y + (sin(degree_to_radian(i)) * LINE_LENGTH);
// 		window->dist[index++] = draw_line(img, window->player.x, window->player.y, line_x, line_y, BOCCHI);
// 		window->dist[index - 1] *= cos(degree_to_radian(window->player.dir - i));
// 		// draw_3D(window, img, index - 1);
// 		printf("distance: %d\n", window->dist[index - 1]);
// 	}
// 	draw_square(img, window->player.x, window->player.y, 3, BOCCHI);
// }

void cast_rays(t_window *window, t_camera *camera) {
	for (int x = 0; x < WINDOW_WIDTH; x++) {
		double cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
		double rayDirX = camera->dirX + camera->planeX * cameraX;
		double rayDirY = camera->dirY + camera->planeY * cameraX;

		int mapX = (int)camera->x;
		int mapY = (int)camera->y;

		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (camera->x - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - camera->x) * deltaDistX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (camera->y - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - camera->y) * deltaDistY;
		}
		while (hit == 0) {
			if (mapX < 0 || (mapX / 64) >= MAP_WIDTH || mapY < 0 || (mapY / 64) >= MAP_HEIGHT)
				break ;
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT && map[mapX][mapY] > 0)
				hit = 1;
		}

	    perpWallDist = (side == 0)
	? (mapX - camera->x + (1 - stepX) / 2) / rayDirX
	: (mapY - camera->y + (1 - stepY) / 2) / rayDirY;
		printf("prewall dist is = %f\n", perpWallDist);
		// perpWallDist *= COL_S; // Scale distance to tile size
		int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist + 50);
		printf("line hight = %i\n", lineHeight);
		// int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawEnd >= WINDOW_HEIGHT) drawEnd = WINDOW_HEIGHT - 1;
		int color;
		if (side == 1) color = grey; // Vertical wall
		else color = 0xFFFFFF; // Horizontal wall
		for (int y = drawStart; y <= drawEnd; y++)
			my_mlx_pixel_put(&window->img, x, y, color);
	}
}

void	draw_scene(t_data *img, t_window *window)//clean the last image and redrawing evreything
{
	static int i;

	if (window->mov.r_right || window->mov.r_left || window->mov.up || window->mov.down || window->mov.left || window->mov.right || !i)
	{
		window->mov.moved = 0;
		if (window->img.img && i)
			mlx_destroy_image(window->mlx, window->img.img);
		window->img.img = mlx_new_image(window->mlx, 1920, 1080);
		window->img.addr = mlx_get_data_addr(window->img.img, &window->img.bits_per_pixel,\
			&window->img.line_length, &window->img.endian);
		// draw_walls(img);
		// draw_player(window, img);
		cast_rays(window, &window->camera);
		// draw_3d(window, img);
		mlx_put_image_to_window(window->mlx, window->win, img->img, 0, 0);
		i = 1;
	}
}
