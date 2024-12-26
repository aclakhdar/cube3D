/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:26:04 by aclakhda          #+#    #+#             */
/*   Updated: 2024/12/26 17:33:00 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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
void	draw_player(t_window *window, t_data *img)//TODO : remake the dda algho
{
	int	line_x;
	int	line_y;
	int	index;

	index = 0;
	for (int i = window->player.dir - FOV / 2; i <= window->player.dir + FOV / 2; i++)
	{
		line_x = window->player.x + (cos(degree_to_radian(i)) * LINE_LENGTH);
		line_y = window->player.y + (sin(degree_to_radian(i)) * LINE_LENGTH);
		window->dist[index++] = draw_line(img, window->player.x, window->player.y, line_x, line_y, BOCCHI);
		printf("distance: %f\n", window->dist[index - 1]);
	}
	draw_square(img, window->player.x, window->player.y, 3, BOCCHI);
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
		draw_walls(img);
		draw_player(window, img);
		// draw_3d(window, img);
		mlx_put_image_to_window(window->mlx, window->win, img->img, 0, 0);
		i = 1;
	}
}
