/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:04:44 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/11 18:06:53 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_data *img, int x_start, int y_start, int color)
{
	int	x;
	int	y;
	int	size;

	size = COL_S;
	y = y_start;
	while (y < y_start + size)
	{
		x = x_start;
		while (x < x_start + size)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_sky(t_data *img, int camera_height, int sky_color)
{
	int	i;
	int	j;

	i = 0;
	while (i < camera_height)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			draw_square(img, j, i, sky_color);
			j += COL_S;
		}
		i += COL_S;
	}
}

void	draw_ground(t_data *img, int start_height, int ground_color)
{
	int	i;
	int	j;

	i = start_height;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			draw_square(img, j, i, ground_color);
			j += COL_S;
		}
		i += COL_S;
	}
}

void	draw_background(t_data *img, t_player *player)
{
	int	camera_height;
	int	pitch;
	int	sky_color;
	int	ground_color;

	pitch = 0;
	camera_height = (WINDOW_HEIGHT / 2) - (pitch * 5);
	if (camera_height < 0)
		camera_height = 0;
	if (camera_height > WINDOW_HEIGHT)
		camera_height = WINDOW_HEIGHT;
	sky_color = (img->r_c << 16) | (img->g_c << 8) | img->b_c;
	ground_color = (img->r_f << 16) | (img->g_f << 8) | img->b_f;
	draw_sky(img, camera_height, sky_color);
	draw_ground(img, camera_height, ground_color);
}
